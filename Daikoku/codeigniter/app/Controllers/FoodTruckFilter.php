<?php

namespace App\Controllers;
use App\Models\FoodTrucksModel;
use App\Models\MainMediaModel;
use App\Models\MenuProductModel;
use CodeIgniter\API\ResponseTrait;
use CodeIgniter\Security\Security;



class FoodTruckFilter extends BaseController
{

    use ResponseTrait;
    protected $security;

    public function __construct() {
        $this->security = service('security');
    }


    public function FoodTrucks(){

        //Get database tables instances
        $FOmodel = model(FoodTrucksModel::class);
        $MPmodel = model(MenuProductModel::class);

        //Get Foodtrucks (that are published), get filter possibilities

        $CountryFilter = $FOmodel->distinct()->select('Country')->where('Published', true)->findAll();
        $KitchenFilter = $FOmodel->distinct()->select('Kitchen')->where('Published', true)->findAll();
        $VehicleFilter = $FOmodel->distinct()->select('Vehicle')->where('Published', true)->findAll();


        $MinPrice = $MPmodel->selectMin('Price')
        ->join($FOmodel->getTable(), $FOmodel->getTable() . '.Name = ' . $MPmodel->getTable() . '.FoodTruckName')
        ->where($FOmodel->getTable() . '.Published', true)
        ->findAll()[0]['Price'];
    
    $MaxPrice = $MPmodel->selectMax('Price')
        ->join($FOmodel->getTable(), $FOmodel->getTable() . '.Name = ' . $MPmodel->getTable() . '.FoodTruckName')
        ->where($FOmodel->getTable() . '.Published', true)
        ->findAll()[0]['Price'];

        $PriceRangeFilter = array(
            'MinPrice' => ceil($MinPrice),
            'MaxPrice' => ceil($MaxPrice)
        );


        //Make a JSON template containing all relevant data of the food truck.
        $data[0] = $CountryFilter;
        $data[1] = $KitchenFilter;
        $data[2] = $VehicleFilter;
        $data[3] = $PriceRangeFilter;
        $data['title'] = ucfirst('Food trucks');
    


        
        return view('templates/header', array(['data' => $data,'title' => ucfirst("Foodtruckspage")])[0])
        . view('pages/Foodtruckspage.php')
        . view('templates/footer');

    }

    public function LoadFoodTrucks(){

        $FOmodel = model(FoodTrucksModel::class);
        $FoodTrucks = $FOmodel->getFoodTrucks();
        $MainMediaModel = model(MainMediaModel::class);



        for($index = 0; $index < count($FoodTrucks); ++$index){
            $FtName = $FoodTrucks[$index]['Name'];

            $Mainpic = $MainMediaModel->select("FileName")
            ->where([
                "FoodTruckName" => $FtName
            ])->first();
            
            if ($Mainpic){
                $FoodTrucks[$index]['Media'] = $Mainpic['FileName'];
            }
            else{
                $FoodTrucks[$index]['Media'] = null;
            }

        }

        return $this->respond($FoodTrucks);


    }



public function Filter()
{
    $post = $this->request->getJSON();
    $newCsrfToken = $this->security->getCSRFhash();
    $CountryChecks = (array) $post->CountryFilter;
    $Countrydata = array_keys($CountryChecks);
    $KitchenChecks = (array) $post->KitchenFilter;
    $Kitchendata = array_keys($KitchenChecks);
    $VehicleChecks = (array) $post->VehicleFilter;
    $Vehicledata = array_keys($VehicleChecks);

    $MPmodel = model(MenuProductModel::class);
    $FOmodel = model(FoodTrucksModel::class);
    $MainMediaModel = model(MainMediaModel::class);

    if ($post->SearchBar === '') {
        $FoodTrucksData = $MPmodel->select('FoodTruckName')
            ->distinct()
            ->where('Price <', $post->range)
            ->findAll();
    } else {
        $FoodTrucksData = $MPmodel->select('FoodTruckName')
            ->distinct()
            ->groupStart()
            ->where('Price <', $post->range)
            ->like('FoodTruckName', $post->SearchBar)
            ->groupEnd()
            ->findAll();
    }

    if (empty($FoodTrucksData)) {
        $FoodTrucksData = [];
    } else {
        $FOmodel->groupStart();
        //Countries
        if (!empty($Countrydata)){
            $FOmodel->groupStart();
            foreach ($Countrydata as $index => $Country){
                if($index == 0){
                    $FOmodel->like('Country', $Country);
                }
                else{
                    $FOmodel->orLike('Country', $Country);
                }
            }
            $FOmodel->groupEnd();
        }

        

        //Kitchens
        if (!empty($Kitchendata)){
            $FOmodel->groupStart();
            foreach ($Kitchendata as $index => $Kitchen){
                if($index == 0){
                    $FOmodel->like('Kitchen', $Kitchen);
                }
                else{
                    $FOmodel->orLike('Kitchen', $Kitchen);
                }
            }
            $FOmodel->groupEnd();
        }

    

        //Vehicles
        if(!empty($Vehicledata)){
            $FOmodel->groupStart();
            foreach ($Vehicledata as $index => $Vehicle){
                if($index == 0){
                    $FOmodel->like('Vehicle', $Vehicle);
                }
                else{
                    $FOmodel->orLike('Vehicle', $Vehicle);
                }
            }
            $FOmodel->groupEnd();
        }


        $FOmodel->groupStart();
        foreach ($FoodTrucksData as $index => $FoodTruck){
            if($index == 0){
                $FOmodel->like('Name', $FoodTruck['FoodTruckName']);
            }
            else{
                $FOmodel->orLike('Name', $FoodTruck['FoodTruckName']);
            }
        }
        $FOmodel->groupEnd();
        

        $FOmodel->groupEnd();
        $FoodTrucks = $FOmodel->where('Published', true)->findAll();

        foreach ($FoodTrucks as $index => $truck) {
            $FtName = $truck['Name'];
            $Mainpic = $MainMediaModel->select("FileName")
                ->where([
                    "FoodTruckName" => $FtName
                ])->first();

            $FoodTrucks[$index]['Media'] = $Mainpic ? $Mainpic['FileName'] : null;
        }
    }

    $data['FoodTrucks'] = $FoodTrucks ?? [];
    $data['newCSRFtoken'] = $newCsrfToken;

    return $this->respond($data);
}

}