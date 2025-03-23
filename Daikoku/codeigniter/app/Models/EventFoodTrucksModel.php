<?php

namespace App\Models;

use CodeIgniter\Model;

class EventFoodTrucksModel extends Model
{
    protected $table = 'eventfoodtrucks';

    protected $allowedFields = [
    'FoodTruckName',
    'EventName',
    "Date"
    ];
}