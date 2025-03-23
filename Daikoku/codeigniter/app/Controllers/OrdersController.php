<?php

namespace App\Controllers;

use App\Models\FoodTrucksModel;
use App\Models\OrderModel;
use App\Models\ReviewModel;
use App\Models\ShoppingCartModel;
use App\Models\UserModel;
use Config\Services;

class OrdersController extends BaseController
{

    public function LoadOrders(){

        $Ordermodel = model(OrderModel::class);
        $Cartmodel = model(ShoppingCartModel::class);


        if (session("UserType") == "C"){
            $Orders = $Ordermodel->where("User", session("NickName"))->orderBy("OrderTime", "DESC")->findAll();

            foreach ($Orders as $index => $Order){
                $OrderedProducts = $Cartmodel->where([
                    "User" => session("NickName"), 
                    "Order_ID" => $Order["Order_ID"]
                    ])->findAll();
                $Orders[$index]["Products"] = $OrderedProducts;
            }
        }
        else{
            $FOmodel = model(FoodTrucksModel::class);
            $FoodTruck = $FOmodel->select('Name')->where("Email", session("Email"))->findAll();
            $Orders = $Ordermodel->where("FoodTruckName", $FoodTruck[0]['Name'])->orderBy("OrderTime", "DESC")->findAll();

            foreach ($Orders as $index => $Order){
                $OrderedProducts = $Cartmodel->where([
                    "FoodTruckName" => $FoodTruck[0]['Name'], 
                    "Order_ID" => $Order["Order_ID"]
                    ])->findAll();
                $Orders[$index]["Products"] = $OrderedProducts;
            }
        }


        return view('templates/header', array(['Orders' => $Orders,'title' => ucfirst("Orders")])[0])
        . view('pages/Orders.php')
        . view('templates/footer');
    }


    public function ConfirmOrder(){
        $Ordermodel = model(OrderModel::class);
        $Cartmodel = model(ShoppingCartModel::class);
        $UserModel = model(UserModel::class);

        $Orders = $Ordermodel->findAll();

        $CartProducts = $Cartmodel->where([
            "User" => session("NickName"),
            "Order_ID" => null
        ])->findAll();

        $FoodTruck = $CartProducts[0]["FoodTruckName"];
        $NewOrder_ID = $this->generateOrderID($Orders);

        $OrderData = [
            "Order_ID" => $NewOrder_ID,
            "User" => session("NickName"),
            "PickUpTime" => null,
            "TotalPrice" => $this->request->getPost("TotalPrice"),
            "FoodTruckName" => $FoodTruck,
            "PickedUp" => false
        ];

        $UserEmail = ($UserModel->select("Email")->where("NickName", $OrderData["User"])->findAll())[0]["Email"];

        $this->NotifyUserAboutOrderConfirmation($UserEmail, $OrderData);

        //Adds order to the orders table.
        $Ordermodel->insert($OrderData);

        //Products receive the created Order_ID when they're ordered. This way we can find them more quickly
        $Cartmodel->where([
            "User" => session("NickName"),
            "Order_ID" => null
        ])->set("Order_ID", $NewOrder_ID)->update();

        return redirect()->to(base_url("Orders"))->with("succes", "Order confirmed succesfully!");

    }

    private function generateOrderID($ExistingOrders){
        $ID = random_int(1000, 999999);
        if (!empty($ExistingOrders)){
            foreach($ExistingOrders as $Order){
                if ($Order["Order_ID"] == $ID){
                    return $this->generateOrderID($ExistingOrders);
                }
            }
        }
        return $ID;
    }


    public function ChangeOrderSettings($OrderNumber){

        $OrderModel = model(OrderModel::class);
        $UserModel = model(UserModel::class);

        $PickUpDate = $this->request->getPost("PickUpTime");
        $Status = $this->request->getPost("Status");

        $Order = ($OrderModel->where("Order_ID", $OrderNumber)->findAll())[0];

        //If nothing has changed for the order settings, don't do anything:
        if ($Order["PickupTime"] != $PickUpDate || $Order["Status"] != $Status){
            $UserEmail = ($UserModel->select("Email")->where("NickName", $Order["User"])->findAll())[0]["Email"];
            $this->NotifyUserAboutOrderUpdates($UserEmail, $Order, $PickUpDate, $Status);

            $OrderModel->where("Order_ID", $OrderNumber)->set([
                "PickupTime" => (($PickUpDate == "")? null : $PickUpDate),
                "Status" => $Status
            ])->update();
        }

        return redirect()->to(base_url("Orders"))->with("succes", "Order settings changed succesfully!");        
    }

    public function PickUpOrder($OrderNumber){

        $OrderModel = model(OrderModel::class);
        $UserModel = model(UserModel::class);


        $Order = $OrderModel->where([
            "User" => session("NickName"),
            "Order_ID" => $OrderNumber
        ])->findAll();

        $OrderModel->where([
            "User" => session("NickName"),
            "Order_ID" => $OrderNumber
        ])->set("PickedUp", true)->update();

        $UserEmail = ($UserModel->select("Email")->where("NickName", $Order[0]["User"])->findAll())[0]["Email"];

        if ($Order[0]["PickedUp"] == false){
            $this->NotifyUserAboutOrderCompletion($UserEmail, $Order[0]);
        }

        return redirect()->to(base_url("Orders"))->with("succes", "Order completed succesfully!");

    }

    public function ReviewOrder($OrderNumber){
        
        
        if (session()->has('LoggedIn')){
            $OrderModel = model(OrderModel::class);
            $Cartmodel = model(ShoppingCartModel::class);
            $Order = $OrderModel->where([
                "User" => session("NickName"),
                "Order_ID" => $OrderNumber
            ])->findAll();

            $OrderedProducts = $Cartmodel->where([
                "User" => session("NickName"), 
                "Order_ID" => $Order[0]["Order_ID"]
                ])->findAll();

            $Order[0]["Products"] = $OrderedProducts;

            return view('templates/header', ['Order' => $Order[0],'title' => ucfirst("OrderReview")])
            . view('pages/OrderReview.php')
            . view('templates/footer');
        }
        else{
            return redirect()->to(base_url("Login"))->with("failure", "Couldn't review due to inactive user session, please log in!");
        }
    }



    public function WriteOrderReview($OrderNumber, $FoodTruckName){

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

        return redirect()->to(base_url("Orders/OrderReview/" . $OrderNumber))->with("succes", "Review sent succesfully!");

    }

    private function NotifyUserAboutOrderUpdates($UserEmail, $Order, $PickUpDate, $Status){
        $email = Services::email();

        //Prepare email information:
        $email->setFrom("daikokuentreprise@gmail.com", "Daikoku");
        $email->setTo($UserEmail);
        $email->setSubject("Order notification: " . $Order['Order_ID']);

        $message = '<h2>Dear Customer,</h2>';
        $message .= '<p>We would like to notify you about your order: </p>';


        //The status has been changed:
        if ($Status != $Order["Status"]){
            $message .= '<h3> Status changes </h3>';
            if ($Status == "Processing"){
                $message .= '<p><strong>Hmm, let\'s take a look:</strong></p><p>Your order is currently being processed by ' . $Order["FoodTruckName"] . '</p>';
            }
            else if ($Status == "Preparation"){
                $message .= '<p><strong>We are almost there!:</strong></p><p>Your order is currently being prepared by ' . $Order["FoodTruckName"] . '</p>';
            }
            else if($Status == "Ready"){
                $message .= "<p><strong>Fresh off the grill and ready to thrill!:</strong></p><p>Your order is ready! Pick it up before it gets cold!</p>";
            }
        }

        //A pickupdate has been set:
        if ($PickUpDate != "" && $Order["PickupTime"] == null){
            $message .= '<h3> Pick up time changes </h3><p>' . $Order["FoodTruckName"] .' has set a pick up date for your order!</p>';
        }
        else if($PickUpDate != "" && $Order["PickupTime"] != null){
            $message .= '<h3> Pick up time changes </h3><p>' . $Order["FoodTruckName"] .' has changed the pick up date for your order!</p>';
        }

        $message .= '<br><p>Kind regards,</p><br><p>Daikoku Entreprise<p>';

        $email->setMessage($message);

        if ($email->send()) {
            echo 'Email sent successfully!';
        } else {
            echo 'Error sending email: ' . $email->printDebugger(['headers']);
        }

    }

    private function NotifyUserAboutOrderConfirmation($UserEmail, $Order){
        $email = Services::email();

        //Prepare email information:
        $email->setFrom("daikokuentreprise@gmail.com", "Daikoku");
        $email->setTo($UserEmail);
        $email->setSubject("New order placed: " . $Order['Order_ID']);

        $message = '<h2>Dear Customer,</h2>';
        $message .= '<p>Your order has been confirmed and received by ' . $Order["FoodTruckName"] . '</p>';
        $message .= '<br><p>Kind regards,</p><br><p>Daikoku Entreprise<p>';

        $email->setMessage($message);

        if ($email->send()) {
            echo 'Email sent successfully!';
        } else {
            echo 'Error sending email: ' . $email->printDebugger(['headers']);
        }

    }

    private function NotifyUserAboutOrderCompletion($UserEmail, $Order){
        $email = Services::email();

        //Prepare email information:
        $email->setFrom("daikokuentreprise@gmail.com", "Daikoku");
        $email->setTo($UserEmail);
        $email->setSubject("Order picked up: " . $Order['Order_ID']);

        $message = '<h2>Dear Customer,</h2>';
        $message .= '<p>Thank you for picking up your order and purchasing at ' . $Order["FoodTruckName"] . '!</p>';
        $message .= '<p>You can review the order, by clicking <a href="' . base_url("Orders/OrderReview/" . $Order["Order_ID"]) .'" >here</a></p>';
        $message .= '<br><p>Kind regards,</p><br><p>Daikoku Entreprise & ' . $Order["FoodTruckName"] . '<p>';

        $email->setMessage($message);

        if ($email->send()) {
            echo 'Email sent successfully!';
        } else {
            echo 'Error sending email: ' . $email->printDebugger(['headers']);
        }

    }




}