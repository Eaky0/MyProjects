<?php

namespace App\Controllers;
use App\Models\FoodTrucksModel;
use App\Models\MainMediaModel;
use App\Models\MediaModel;
use App\Models\MenuCategoryModel;
use App\Models\MenuProductModel;
use App\Models\ReviewModel;
use CodeIgniter\API\ResponseTrait;
use CodeIgniter\Security\Security;


class FoodTruckInfo extends BaseController
{
    use ResponseTrait;

    public function LoadInfo($FoodTruckName){
        //Get database tables instances
        $FOmodel = model(FoodTrucksModel::class);
        $MPmodel = model(MenuProductModel::class);
        $MCmodel = model(MenuCategoryModel::class);
        $MediaModel = model(MediaModel::class);
        $MainMediaModel = model(MainMediaModel::class);
        $Reviews = model(ReviewModel::class);

        //Find owner of foodtruck through email, Find categories added by owner, Find Foodtruck menus of owner, Find photos of owner.

        $Rating = $Reviews->selectAvg('Rating')->where('FoodTruckName', $FoodTruckName)->findAll();
        $FOmodel->where('Name', $FoodTruckName)->set('Rating', $Rating[0]['Rating'])->update();

        $FoodTruck = $FOmodel->where("Name", $FoodTruckName)->findAll();
        $Categories = $MCmodel->select("Category")->where("FoodTruckName", $FoodTruck[0]['Name'])->findAll();
        $Menus = $MPmodel->where("FoodTruckName", $FoodTruck[0]['Name'])->findAll();
        $MainMedia = $MainMediaModel->select("FileName")->where([
            "FoodTruckName" => $FoodTruck[0]['Name']
        ])->findAll();

        $FoodTruck[0]["Media"] = $MainMedia;

        //Find Pictures of each menu specificially
        for($index = 0; $index < count($Menus); ++$index){
            $MenuMedia = $MediaModel->where([
                "FoodTruckName" => $FoodTruck[0]['Name'],
                "MenuName" => $Menus[$index]['Name'],
            ])->findAll();
            $Menus[$index]['Media'] = $MenuMedia;

        }

        for($index = 0; $index < count($Menus); ++$index){
            $MenuReviews = $Reviews->where([
                "FoodTruckName" => $FoodTruck[0]['Name'],
                "MenuName" => $Menus[$index]['Name'],
            ])->findAll();

            $Menus[$index]['Reviews'] = $MenuReviews;

        }

        

        


        //Make a JSON template containing all relevant data of the food truck.
        $data = $FoodTruck;
        $data[1] = $Categories;
        $data[2] = $Menus;

        return view('templates/header', array(['data' => $data,'title' => ucfirst("Foodtruckinfopage")])[0])
        . view('pages/Foodtruckinfopage.php')
        . view('templates/footer');
    }

    public function WriteReview($FoodTruckName){

        $Reviews= model(ReviewModel::class);
        $FOmodel = model(FoodTrucksModel::class);

        $NewReview = [
            'MenuName' => $this->request->getPost("MenuName"), 
            'FoodTruckName' => $FoodTruckName,
            'Review' => $this->request->getPost("ReviewText"), 
            'User' => session("NickName"), 
            'Timestamp' => date('Y-m-d H:i:s'),
            'Rating' => $this->request->getPost("Rating")
        ];

        $Reviews->insert($NewReview);


        $Rating = $Reviews->selectAvg('Rating')->where('FoodTruckName', $FoodTruckName)->findAll();
        $FOmodel->where('Name', $FoodTruckName)->set('Rating', $Rating[0]['Rating'])->update();

        
        return redirect()->to(base_url("Foodtruckinfopage/" . $FoodTruckName))->with("succes", "Review sent succesfully!");

    }


    public function getMenus(){
        $FOmodel = model(FoodTrucksModel::class);
        $MenuModel = model(MenuProductModel::class);
        $FoodTruck = $FOmodel->where("Email", session("Email"))->findAll();
        $MenusOfFoodTruck = $MenuModel->where("FoodTruckName", $FoodTruck[0]["Name"])->findAll();
        return $this->respond($MenusOfFoodTruck);
    }

}