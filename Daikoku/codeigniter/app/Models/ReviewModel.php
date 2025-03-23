<?php

namespace App\Models;

use CodeIgniter\Model;

class ReviewModel extends Model
{
    protected $table = 'reviews';

    protected $allowedFields = ['MenuName', 'FoodTruckName', 'Review', 'User', 'Timestamp', 'Rating'];

}