<?php

namespace App\Controllers;
use App\Models\UserModel;

class LoginChecker extends BaseController
{


    /* Method: Checks the Email address, Password and Usertype given by a user.
     * If correct, a session starts and the user is redirected to the Mainpage.
     * If incorrect, user is redirected to the Login page and gets a warning that he couldn't enter, either due to wrong Email or Password or a wrong format for the Password and Email.
     */
    public function loginUser(){
        $Usermodel = model(UserModel::class);
        $Email = $this->request->getPost('Email');
        $Password = $this->request->getPost('Password');
        $Usertype = $this->request->getPost('C-FO');


        $user = ($Usermodel->where(["Email" => $Email,
                                    "Password" => $Password,
                                    "UserType" => $Usertype
                                    ])->findAll()[0]);
        $user['LoggedIn'] = true;

        session()->set($user);

        helper('cookie');
        $cookieExpiration = 3600;
        set_cookie('ci_session_cookie', session_id(), $cookieExpiration);


        return redirect()->to(base_url('Mainpage'))->with('Succes','Login Succesful');

    }



    public function logoutUser(){
        session()->destroy();

        helper('cookie');
        delete_cookie('ci_session_cookie');
        

        $BacktoMain['title'] = ucfirst("Mainpage");
        return redirect()->to(base_url("Mainpage"))->with('Succes','Logout Succesful');

    }

}