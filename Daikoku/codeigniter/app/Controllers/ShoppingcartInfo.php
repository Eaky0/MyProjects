<?php

namespace App\Controllers;

use App\Models\ShoppingCartModel;


class ShoppingCartInfo extends BaseController
{

    public function LoadCart(){

        $SCmodel = model(ShoppingCartModel::class);

        $OrderedProducts = $SCmodel->where([
            "User" => session("NickName"),
            "Order_ID" => null
            ])->findAll();


        $TotalPrice = 0;

        foreach($OrderedProducts as $OrderedProduct){
            $ProductPrice = $OrderedProduct['ProductPrice'] * $OrderedProduct['Amount'];
            $TotalPrice += $ProductPrice;
        }

        return view('templates/header', array(['totalprice' => $TotalPrice, 'ShoppingCartProducts' => $OrderedProducts,'title' => ucfirst("Shoppingcart")])[0])
        . view('pages/Shoppingcart.php')
        . view('templates/footer');
    }
        
    

    public function AddProduct($FoodTruckName){
        $SCmodel = model(ShoppingCartModel::class);

        $Order = $SCmodel->where([
            "User" => session("NickName"),
            "Order_ID" => null
            ])->findAll();


        //If the cart already contains this product, the given amount will be added to the existing one.
        if ($this->HasProduct($Order, $this->request->getPost("ProductName"))){
            $SCmodel->where([
                "ProductName" => $this->request->getPost("ProductName"),
                "User" => session("NickName"),
                "Order_ID" => null,
                "FoodTruckName" => $FoodTruckName
            ])->set("Amount", "Amount + " . $this->request->getPost("ProductAmount"), false)
            ->update();
        }
        //Otherwise, it will be added as a new product to the cart.
        else{

            $NewProduct = [
                "User" => session("NickName"),
                "ProductName" => $this->request->getPost("ProductName"),
                "ProductPrice" => $this->request->getPost("ProductPrice"),
                "Order_ID" => null,
                "Amount" => $this->request->getPost("ProductAmount"),
                "FoodTruckName" => $FoodTruckName
            ];
    
            $SCmodel->insert($NewProduct);    
        }
        return redirect()->to(base_url("Foodtruckinfopage/" . $FoodTruckName))->with("succes", "Product added succesfully to shopping cart!");
    }

    private function HasProduct($Order, $ProductName){
        foreach($Order as $OrderedProduct){
            if ($OrderedProduct["ProductName"] == $ProductName){
                return true;
            }
        }
        return false;

    }

    public function ChangeAmount(){
        $SCmodel = model(ShoppingCartModel::class);

        $SCmodel->where([
            "FoodTruckName" => $this->request->getPost("FoodTruckName"),
            "ProductName" =>  $this->request->getPost("ProductName"),
            "User" => session("NickName"),
            "Order_ID" => null
        ])->set("Amount", $this->request->getPost("ProductAmount"))->update();

        return redirect()->to(base_url("Shoppingcart"))->with("succes", "Product amount changed succesfully in shopping cart!");


    }


    public function DeleteFromCart(){
        $SCmodel = model(ShoppingCartModel::class);

        $SCmodel->where([
            "FoodTruckName" => $this->request->getPost("FoodTruckName"),
            "ProductName" =>  $this->request->getPost("ProductName"),
            "User" => session("NickName"),
            "Order_ID" => null
        ])->delete();

        return redirect()->to(base_url("Shoppingcart"))->with("succes", "Product was deleted succesfully from the shopping cart!");
    }


}