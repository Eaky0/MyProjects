<?php

namespace App\Models;

use CodeIgniter\Model;

class OrderModel extends Model
{
    protected $table = 'orders';
    protected $allowedFields = ['Order_ID', 'User', 'OrderTime','PickupTime','FoodTruckName','PickedUp', 'Status',  'TotalPrice'];
}