<?php

namespace App\Models;

use CodeIgniter\Model;

class MenuProductModel extends Model
{
    protected $table = 'menu';

    protected $allowedFields = [
        'Name',
        'Price',
        'Description',
        'Ingredients',
        'Allergenes',
        'Category',
        'FoodTruckName'
        ];
}