<?php

namespace App\Models;

use CodeIgniter\Model;

class MenuCategoryModel extends Model
{
    protected $table = 'foodtruckcategories';

    protected $allowedFields = [
        'FoodTruckName',
        'Category'
        ];
}