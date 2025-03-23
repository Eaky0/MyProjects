<?php

namespace App\Controllers;

use App\Models\EventFoodTrucksModel;
use CodeIgniter\Exceptions\PageNotFoundException;
use App\Models\FoodTrucksModel;
use App\Models\EventsModel;
use App\Models\MainMediaModel;

class Pages extends BaseController
{
    public function index()
    {
        return view('welcome_message');
    }

    public function main()
    {
        $FTmodel = model(FoodTrucksModel::class);
        $EVmodel = model(EventsModel::class);

        $MainMediaModel = model(MainMediaModel::class);


        $data['title'] = ucfirst('Mainpage');
        $data['foodtrucks'] = $FTmodel->getFoodTrucks();
        $data['events'] = $EVmodel->getMainUpcomingEvents();
        

        for($index = 0; $index < count($data['foodtrucks']); ++$index){
            $FtName = $data['foodtrucks'][$index]['Name'];

            $Mainpic = $MainMediaModel->select("FileName")
            ->where([
                "FoodTruckName" => $FtName
            ])->first();
            
            if ($Mainpic){
                $data['foodtrucks'][$index]['Media'] = $Mainpic['FileName'];
            }
            else{
                $data['foodtrucks'][$index]['Media'] = null;
            }

        }


        return view('templates/header', $data)
        . view('pages/Mainpage.php')
        . view('templates/footer');
    }
    

    public function events()
    {
        $EVmodel = model(EventsModel::class);

        $data['title'] = ucfirst('Eventspage');
        $data['upcomingEvents'] = $EVmodel->getUpcomingEvents();
        $data['previousEvents'] = $EVmodel->getPreviousEvents();
        
        return view('templates/header', $data)
        . view('pages/Eventspage.php')
        . view('templates/footer');
    }

    public function showEvent($EventName, $EventDate){

        $EVmodel = model(EventsModel::class);
        $EVFmodel = model(EventFoodTrucksModel::class);
        $FTmodel = model(FoodTrucksModel::class);
        $MainMediaModel = model(MainMediaModel::class);



        $Event = $EVmodel->select('*')->where([
            "EventName" => $EventName,
            "Date" => $EventDate
        ])->findAll();

        $EventFoodTrucks = $EVFmodel->where([
            "EventName" => $Event[0]['EventName'],
            "Date" => $EventDate
        ])->findAll();


        $FoodTrucks = $FTmodel->getFoodTrucks();

        $foodTrucksForEvent = array_filter($FoodTrucks, function($foodTruck) use ($EventFoodTrucks) {
            foreach ($EventFoodTrucks as $eventFoodTruck) {
                if ($foodTruck['Name'] === $eventFoodTruck['FoodTruckName']) {
                    return true;
                }
            }
            return false;
        });

        

        $data = $Event;
        $data[1] = array_values($foodTrucksForEvent);

        for($index = 0; $index < count($data[1]); ++$index){
            $FtName = $data[1][$index]['Name'];

            $Mainpic = $MainMediaModel->select("FileName")
            ->where([
                "FoodTruckName" => $FtName
            ])->first();
            
            if ($Mainpic){
                $data[1][$index]['Media'] = $Mainpic['FileName'];
            }
            else{
                $data[1][$index]['Media'] = null;
            }

        }

        

        return view('templates/header', array(['data' => $data,'title' => ucfirst("EventInfopage")])[0])
        . view('pages/EventInfopage.php')
        . view('templates/footer');
    }
    

    
    public function view($page = 'home')
    {
        if (!is_file(APPPATH . 'Views/pages/' . $page . '.php')) {
            // Whoops, we don't have a page for that!
            throw new PageNotFoundException($page);
        }

        if($page == "Login"){
            helper('form');
        }

        $data['title'] = ucfirst($page); // Capitalize the first letter

        return view('templates/header', $data)
            . view('pages/' . $page)
            . view('templates/footer');
    }

}