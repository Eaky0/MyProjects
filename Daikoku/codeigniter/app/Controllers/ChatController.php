<?php

namespace App\Controllers;

use App\Models\EventFoodTrucksModel;
use CodeIgniter\Exceptions\PageNotFoundException;
use App\Models\FoodTrucksModel;
use App\Models\EventsModel;
use App\Models\MainMediaModel;
use CodeIgniter\API\ResponseTrait;
use App\Models\ChatModel;


class ChatController extends BaseController
{

    use ResponseTrait;
    protected $security;

    public function __construct() {
        $this->security = service('security');
    }

    public function LoadChats(){
        $ChatModel = model(ChatModel::class);


        if (session("UserType") == "C"){
            $Contacts = $ChatModel->distinct()->select("ToUser")->where("FromUser", session("NickName"))->findAll();
        }
        else{
            $FOmodel = model(FoodTrucksModel::class);
            $FoodTruckName = ($FOmodel->where("Email",session('Email'))->findAll())[0]['Name'];
            $Contacts = $ChatModel->distinct()->select("FromUser")->where("ToUser", $FoodTruckName)->findAll();
        }



        return view('templates/header', array(['Contacts' => $Contacts,'title' => ucfirst("Chatpage")])[0])
        . view('pages/Chatpage.php')
        . view('templates/footer');


    }

    public function ViewChatWindow(){

        $ChatModel = model(ChatModel::class);

        $post = $this->request->getJSON();
        $newCsrfToken = $this->security->getCSRFhash();

        $ContactName = $post->Name;


        //Get all messages between the you and the contact ordered by timestamp

        if (session("UserType") == "C"){
        $Chats = $ChatModel
            ->where('FromUser', session("NickName"))
            ->where('ToUser', $ContactName)
            ->orWhere('FromUser', $ContactName)
            ->where('ToUser', session("NickName"))
            ->orderBy('Timestamp', 'ASC')
            ->findAll();
        }
        else{
            $FOmodel = model(FoodTrucksModel::class);
            $FoodTruckName = ($FOmodel->where("Email",session('Email'))->findAll())[0]['Name'];

            $Chats = $ChatModel
            ->where('FromUser', $FoodTruckName)
            ->where('ToUser', $ContactName)
            ->orWhere('FromUser', $ContactName)
            ->where('ToUser', $FoodTruckName)
            ->orderBy('Timestamp', 'ASC')
            ->findAll();
        }


        $post->Chats = $Chats;
        $post->newCSRFtoken = $newCsrfToken;


        return $this->respond($post);

    }

    public function SendChat(){

        $ChatModel = model(ChatModel::class);

        $post = $this->request->getJSON();
        $newCsrfToken = $this->security->getCSRFhash();

        $ContactName = $post->Name;
        $Content = $post->Content;


        if (session("UserType") == 'C'){
            $ChatData = [
                "FromUser" => session("NickName"),
                "ToUser" => $ContactName,
                "Timestamp" => date('Y-m-d H:i:s', time()),
                "Content" => $Content,
            ];
        }
        else{
            $FOmodel = model(FoodTrucksModel::class);
            $FoodTruckName = ($FOmodel->where("Email",session('Email'))->findAll())[0]['Name'];
            $ChatData = [
                "FromUser" => $FoodTruckName,
                "ToUser" => $ContactName,
                "Timestamp" => date('Y-m-d H:i:s', time()),
                "Content" => $Content,
            ];
        }
        
        $ChatModel->insert($ChatData);

        $post->NewChat = $ChatData;
        $post->newCSRFtoken = $newCsrfToken;

        return $this->respond($post);

    }

    public function newChat($FoodTruckName){

        $ChatModel = model(ChatModel::class);

        $Contacts = $ChatModel->distinct()->select("ToUser")->where("FromUser", session("NickName"))->findAll();


        $ContactExists = false;

        foreach ($Contacts as $Contact){
            if ($Contact["ToUser"] == $FoodTruckName){
                $ContactExists = true;
                break;
            }
        }

        if (!$ContactExists){
            $Contacts[]["ToUser"] = $FoodTruckName;
        }

        return view('templates/header', array(['Contacts' => $Contacts, 'OpenChat' => $FoodTruckName, 'title' => ucfirst("Chatpage")])[0])
        . view('pages/Chatpage.php')
        . view('templates/footer');



    }

}