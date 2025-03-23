<?php

namespace App\Models;

use CodeIgniter\Model;

class MainMediaModel extends Model
{
    protected $table = 'mainmedia';

    protected $allowedFields = [
        'FoodTruckName',
        'FileName'
        ];
}