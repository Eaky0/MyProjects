<?php

namespace App\Controllers;

use App\Models\FoodTrucksModel;
use App\Models\UserModel;
use CodeIgniter\API\ResponseTrait;

class SignUpChecker extends BaseController
{
    use ResponseTrait;

    //When clicked on Login, redirects to Login 
    public function SignUp() {
        return view('templates/header', ['title' => 'Login'])
        . view("pages/SignUp.php")
        . view('templates/footer');
    }


    /* Method: Checks the Email address, Password and Usertype given by a user.
     * If correct, a session starts and the user is redirected to the Mainpage.
     * If incorrect, user is redirected to the Login page and gets a warning that he couldn't enter, either due to wrong Email or Password or a wrong format for the Password and Email.
     */
    public function MakeUser(){
        $UserModel = model(UserModel::class);

        $Usertype = $this->request->getPost("C-FO");
        $NewUser = [
            "FirstName" => $this->request->getPost("Fname"),
            "LastName" => $this->request->getPost("Lname"),
            "BirthDate" => $this->request->getPost("BirthDate"),
            "NickName" => $this->request->getPost("UserName"),
            "Email" => $this->request->getPost("Email"),
            "Password" => $this->request->getPost("Password"),
            "UserType" => $Usertype
        ];

        $UserModel->insert($NewUser);

        if ($Usertype == "FO"){
            $FTmodel = model(FoodTrucksModel::class);
            $NewFoodTrucker = [
                "Name" => $this->request->getPost("FTname"),
                "Email" => $this->request->getPost("Email"),
                "Tel" => $this->request->getPost("Tel"),
                "Rating" => 0,
                "Published" => false
            ];

            $FTmodel->insert($NewFoodTrucker);
        }

        $NewUser['LoggedIn'] = true;
        session()->set($NewUser);
        return redirect()->to(base_url('Mainpage'))->with('Succes','Login Succesful');
    }


    public function getUsers(){
        $UserModel = model(UserModel::class);
        $Usernames = $UserModel->findAll();
        return $this->respond($Usernames);
    }

    public function getFoodTrucks(){
        $FTmodel = model(FoodTrucksModel::class);
        $FoodTrucks = $FTmodel->findAll();
        return $this->respond($FoodTrucks);
    }

}