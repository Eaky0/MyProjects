<?php

namespace App\Models;

use CodeIgniter\Model;

class ShoppingCartModel extends Model
{
    protected $table = 'shoppingcart';

    protected $allowedFields = ['User', 'ProductName', 'ProductPrice', 'Amount', 'FoodTruckName', 'Order_ID'];

}