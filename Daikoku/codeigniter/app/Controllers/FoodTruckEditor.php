<?php

namespace App\Controllers;
use App\Models\MenuProductModel;
use App\Models\MenuCategoryModel;
use App\Models\FoodTrucksModel;
use App\Models\MainMediaModel;
use App\Models\MediaModel;

class FoodTruckEditor extends BaseController
{

    public function FTeditor(){

        //Get database tables instances
        $FOmodel = model(FoodTrucksModel::class);
        $MPmodel = model(MenuProductModel::class);
        $MCmodel = model(MenuCategoryModel::class);
        $MediaModel = model(MediaModel::class);
        $MainMediaModel = model(MainMediaModel::class);


        //Find owner of foodtruck through email, Find categories added by owner, Find Foodtruck menus of owner, Find photos of owner.
        $Owner = $FOmodel->where("Email",session('Email'))->findAll();
        $Categories = $MCmodel->select("Category")->where("FoodTruckName", $Owner[0]['Name'])->findAll();
        $Menus = $MPmodel->where("FoodTruckName", $Owner[0]['Name'])->findAll();
        $MainMedia = $MainMediaModel->select("FileName")->where([
            "FoodTruckName" => $Owner[0]['Name']
        ])->findAll();

        $Owner[0]["Media"] = $MainMedia;

        //Find Pictures of each menu specificially
        for($index = 0; $index < count($Menus); ++$index){
            $MenuMedia = $MediaModel->select("FileName")->where([
                "FoodTruckName" => $Owner[0]['Name'],
                "MenuName" => $Menus[$index]['Name'],
            ])->findAll();
            
            $Menus[$index]['Media'] = $MenuMedia;

        }

        //Make a JSON template containing all relevant data of the food truck.
        $data = $Owner;
        $data[0]['title'] = ucfirst("Foodtruckeditor");
        $data[1] = $Categories;
        $data[2] = $Menus;

        
        return view('templates/editorheader', array('data' => $data))
        . view('pages/Foodtruckeditorpage.php')
        . view('templates/footer');

    }


    public function AddMainImageEditor(){
        helper("form");
        
        $FOmodel = model(FoodTrucksModel::class);
        $MainMediamodel = model(MainMediaModel::class);

        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();

        $MediaData = $this->request->getFiles("MainI");

        foreach($MediaData["MainI"] as $MediaItem){
            $FileName = $MediaItem->getRandomName();
            $Itemdata = [
                'FoodTruckName' => $FoodTruck[0],
                'FileName' => $FileName,
            ];

            $MediaItem->move("img/", $FileName);
            $MainMediamodel->insert($Itemdata);
        }

        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'New main images have been added succesfully!');
    }

    public function DeleteMainImageEditor(){
        helper("form");        
        
        $FOmodel = model(FoodTrucksModel::class);
        $MainMediamodel = model(MainMediaModel::class);

        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();

        $MainMediamodel->where([
            "FileName"=> $this->request->getPost("SelectedFile"),
            "FoodTruckName" => $FoodTruck[0]
        ]);
        $MainMediamodel->delete();

        helper('filesystem'); 

        $fileName = $this->request->getPost("SelectedFile");
        $file_path = "img/" . $fileName;
        unlink($file_path); 

        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'Image has been deleted succesfully!');
        
       
    }

    public function NewCategoryEditor(){
        
        helper("form");

        $FOmodel = model(FoodTrucksModel::class);
        $MCmodel = model(MenuCategoryModel::class);

        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();
        $newCategory= $this->request->getPost("NewCategory");

        $categoryData = [
            'FoodTruckName' => $FoodTruck[0],
            'Category' => $newCategory
        ];

        $MCmodel->insert($categoryData);
        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'New category has been added succesfully!');
    }


    public function DeleteCategoryEditor(){
        $FOmodel = model(FoodTrucksModel::class);
        $MPmodel = model(MenuProductModel::class);
        $MCmodel = model(MenuCategoryModel::class);
        $IVmodel = model(MediaModel::class);

        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();

        $Menus = $MPmodel->where([
            "FoodTruckName" => $FoodTruck[0],
            "Category" => $this->request->getPost("Category")
        ])->findAll();

        foreach($Menus as $Menu){
            $CorrespondingFiles = $IVmodel->select("FileName")->where([
                "FoodTruckName" => $FoodTruck[0],
                "MenuName" => $Menu["Name"],
            ])->findAll();
    
            foreach($CorrespondingFiles as $File){
                $file_path = "img/" . $File["FileName"];
                unlink($file_path);
            }

        }

        $MCmodel->where([
            "FoodTruckName" => $FoodTruck[0],
            "Category" => $this->request->getPost("Category")
        ]);
        $MCmodel->delete();

        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'Category has been deleted succesfully!');
    }

    public function NewProductEditor(){

        helper("form");
        
        $FOmodel = model(FoodTrucksModel::class);
        $MPmodel = model(MenuProductModel::class);
        $IVmodel = model(MediaModel::class);

        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();

        $ProductData = [
            'Name' => $this->request->getPost("NewProductName"),
            'Price' => $this->request->getPost("NewProductPrice"),
            'Description' => $this->request->getPost("NewProductDescription"),
            'Ingredients' => $this->request->getPost("NewProductIngredients"),
            'Allergenes' => $this->request->getPost("NewProductAllergenes"),
            'Category' => $this->request->getPost("NewProductCategory"),
            'FoodTruckName' => $FoodTruck[0]
        ];

        $MPmodel->insert($ProductData);

        $MediaData = $this->request->getFiles("NewProductIV");



        foreach($MediaData["NewProductIV"] as $MediaItem){

        if ($MediaItem->isValid() && $MediaItem->getSize() > 0){
                
                $FileName = $MediaItem->getRandomName();
                $Itemdata = [
                    'FoodTruckName' => $FoodTruck[0],
                    'MenuName' => $this->request->getPost("NewProductName"),
                    'FileName' => $FileName,
                ];

                $MediaItem->move("img/", $FileName);
                $IVmodel->insert($Itemdata);
            }   
        }

        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'New product has been added succesfully!');


    }


    public function DeleteProductEditor(){
        $FOmodel = model(FoodTrucksModel::class);
        $MPmodel = model(MenuProductModel::class);
        $IVmodel = model(MediaModel::class);


        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();

        $CorrespondingFiles = $IVmodel->select("FileName")->where([
            "FoodTruckName" => $FoodTruck[0],
            "MenuName" => $this->request->getPost("MenuName"),
        ])->findAll();


        foreach($CorrespondingFiles as $index => $File){
            $file_path = "img/" . $File["FileName"];
            unlink($file_path);
        }


        $MPmodel->where([
            "FoodTruckName" => $FoodTruck[0],
            "Name" => $this->request->getPost("MenuName")
        ]);
        $MPmodel->delete();
        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'New category has been added succesfully!');


    }

    public function addIVEditor(){

        helper("form");
        
        $FOmodel = model(FoodTrucksModel::class);
        $IVmodel = model(MediaModel::class);

        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();


        $MediaData = $this->request->getFiles("ProductIV");

        foreach($MediaData["ProductIV"] as $MediaItem){
        if ($MediaItem->isValid() && $MediaItem->getSize() > 0){
                $FileName = $MediaItem->getRandomName();
                $Itemdata = [
                    'FoodTruckName' => $FoodTruck[0],
                    'MenuName' => $this->request->getPost("MenuName"),
                    'FileName' => $FileName,
                ];

                $MediaItem->move("img/", $FileName);
                $IVmodel->insert($Itemdata);
            }   
        }

        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'New Images and Videos have been added to the corresponding menu succesfully!');

    }

    public function DeleteIVEditor(){
        helper("form");
        
        
        $FOmodel = model(FoodTrucksModel::class);
        $IVmodel = model(MediaModel::class);

        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();

        $IVmodel->where([
            "FileName"=> $this->request->getPost("SelectedFile"),
            "MenuName"=> $this->request->getPost("MenuName"),
            "FoodTruckName" => $FoodTruck[0]
        ]);
        $IVmodel->delete();

        helper('filesystem');

        $fileName = $this->request->getPost("SelectedFile");
        $file_path = "img/" . $fileName; 
        unlink($file_path); 


        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'Image or Video has been deleted from the corresponding menu succesfully!');
    }

    public function EditMainEditor(){
        helper("form");
        
        
        $FOmodel = model(FoodTrucksModel::class);

        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();

        $isPublished = ($this->request->getPost('isPublished') === 'on' ? true : false);

        

        $FOmodel->where("Name", $FoodTruck[0])->set([
            "Header" => $this->request->getPost("DescHeader"),
            "Description" => $this->request->getPost("DescBody"),
            "Country" => $this->request->getPost("Country"),
            "Kitchen" => $this->request->getPost("KitchenType"),
            "Vehicle" => $this->request->getPost("VehicleType"),
            "Published" => $isPublished
            ])->update();
        

        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'Main section has been edited succesfully!');


    }

    public function EditContactEditor(){
        helper("form");
        $FOmodel = model(FoodTrucksModel::class);
        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();


        $FOmodel->where("Name", $FoodTruck[0])->set([
            "Tel" => $this->request->getPost("PhoneNumber"),
            "OpenTime" => $this->request->getPost("OpeningTime"),
            "CloseTime" => $this->request->getPost("ClosingTime"),
            "CurrentLocation" => $this->request->getPost("CurrentLocation"),
            "NextLocation" => $this->request->getPost("NextLocation")
            ])->update();

        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'Contact section has been edited succesfully!');

    }

    public function EditMenuEditor(){
        helper("form");
        
        $FOmodel = model(FoodTrucksModel::class);
        $MPmodel = model(MenuProductModel::class);

        $FoodTruck = $FOmodel->select("Name")->where("Email",session('Email'))->findAll();


        $MPmodel
        ->where(["FoodTruckName" => $FoodTruck[0],
                 "Name" => $this->request->getPost("MenuName")])
        ->set([
            "Name" => $this->request->getPost("ProductName"),
            "Price" => $this->request->getPost("ProductPrice"),
            "Description" => $this->request->getPost("ProductDescription"),
            "Ingredients" => $this->request->getPost("ProductIngredients"),
            "Allergenes" => $this->request->getPost("ProductAllergenes"),
            "Category" => $this->request->getPost("ProductCategory")
            ])->update();

        return redirect()->to(base_url("Foodtruckeditorpage"))->with('Succes', 'Menu has been edited succesfully!');

    }
}
