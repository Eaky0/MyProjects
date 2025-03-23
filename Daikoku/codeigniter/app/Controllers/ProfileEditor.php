<?php

namespace App\Controllers;

use App\Models\FoodTrucksModel;
use App\Models\OrderModel;
use App\Models\ShoppingCartModel;
use App\Models\UserModel;

class ProfileEditor extends BaseController
{
    /* Method: Loads the Profile page for the user.
     * PRE: Profile dropdown button has to be clicked
     * PRE: Any attribute has been edited.
     */
    public function LoadProfile(){

        if (session("UserType") == "FO"){
            $FOmodel = model(FoodTrucksModel::class);
            $Ordermodel = model(OrderModel::class);
            $CartModel = model(ShoppingCartModel::class);
        
            $FoodTruckName = ($FOmodel->where("Email", session("Email"))->findAll())[0];
            $OrderAmount = $Ordermodel->where("FoodTruckName", $FoodTruckName["Name"])->findAll();

            $TopProducts = $CartModel
            ->select('ProductName, SUM(Amount) as TotalAmount')
            ->where('FoodTruckName', $FoodTruckName["Name"])
            ->where('Order_ID IS NOT NULL', null, false)
            ->groupBy('ProductName')
            ->orderBy('TotalAmount', 'DESC')
            ->limit(3)
            ->findAll();

            $Statistics["OrderAmount"] = count($OrderAmount);
            $Statistics["FoodTruck"] = $FoodTruckName;
            $Statistics["Top3Products"] = $TopProducts;
            $Statistics["title"] = "Profilepage";
            
        }
        else{
            $Statistics["title"] = "Profilepage";
        }


        return view('templates/header', $Statistics)
        . view('pages/Profilepage.php')
        . view('templates/footer');
        
    }

    


    /* Method: sets new values for the first name, last name, birthdate and password attributes.
     * PRE: savebutton has been clicked!
     * PRE: Any attribute has been edited.
     */
    public function editProfile($page = "Profilepage"){
        helper('form');


        $Users = model(UserModel::class);
        
        $Users->where('NickName',session('NickName'))->set(array(
            'FirstName' => $this->request->getPost("Fname"),
            'LastName' => $this->request->getPost("Lname"),
            'BirthDate' => $this->request->getPost("BirthDate"),
            'Password' => $this->request->getPost("Password")))->update();

        session()->set(array(
            'FirstName' => $this->request->getPost("Fname"),
            'LastName' => $this->request->getPost("Lname"),
            'BirthDate' => $this->request->getPost("BirthDate"),
            'Password' => $this->request->getPost("Password")
        ));

        return redirect()->to(base_url($page))->with('Succes', 'Profile has been edited succesfully!');
    }


    public function editProfilePicture(){

        $UserModel = model(UserModel::class);
        $NewPfp = $this->request->getFile("Pfp");

        $OldPfp = ($UserModel->select("ProfilePicture")->where("NickName", session("NickName"))->findAll())[0]["ProfilePicture"];

        if ($OldPfp !== null){
            $filepath = "img/" . $OldPfp;
            unlink($filepath);
        }

        $FileName = $NewPfp->getRandomName();
        $NewPfp->move("img/", $FileName);
        session()->set("ProfilePicture", $FileName);
        $UserModel->where("NickName", session("NickName"))->set("ProfilePicture", $FileName)->update();
    
        return redirect()->to(base_url("Profilepage"))->with('Succes', 'Profile picture has been changed succesfully!');

    }

}
