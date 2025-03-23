<?php

namespace App\Controllers;

use Config\Services;

class ContactController extends BaseController
{

    public function SendMessage(){

        $email = Services::email();

        //Prepare email information:
        $email->setFrom($this->request->getPost("Email"));
        $email->setTo("daikokuentreprise@gmail.com");
        $email->setSubject("Question from " . $this->request->getPost("Email"));

        $message = '<p>' . $this->request->getPost("MsgText") . '</p>';
        $email->setMessage($message);
        
        if ($email->send()) {
            echo 'Email sent successfully!';
        } else {
            echo 'Error sending email: ' . $email->printDebugger(['headers']);
        }

        return redirect()->to(base_url("Contactpage"))->with('Succes', 'Message has been sent succesfully!');

    }

}