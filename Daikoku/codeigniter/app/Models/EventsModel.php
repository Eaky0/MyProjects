<?php

namespace App\Models;

use CodeIgniter\Model;

class EventsModel extends Model
{
    protected $table = 'events';

    protected $allowedFields = [
    'EventName',	
    'Date',	
    'Header',	
    'Description',	
    'StartTime',	
    'EndTime',	
    'Upcoming'];

    public function getEvents()
    {
        return $this->findAll();
    }

    public function getUpcomingEvents(){
        return $this->where(['Upcoming' => true])->findAll();
    }

    public function getMainUpcomingEvents(){
        return $this->where(['Upcoming' => true])->limit(2)->findAll();
    }

    public function getPreviousEvents(){
        return $this->where(['Upcoming' => false])->findAll();
    }

}