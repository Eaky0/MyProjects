<?php

namespace App\Models;

use CodeIgniter\Model;

class FoodTrucksModel extends Model
{
    protected $table = 'foodtrucks';

    protected $allowedFields = [
        'Name',
        'Email',	
        'Tel',	
        'OpenTime',	
        'CloseTime',	
        'CurrentLocation',
        'NextLocation',
        'Header',	
        'Description',	
        'Country',	
        'Kitchen',	
        'Vehicle',	
        'Rating',
        'Published'];

    public function getFoodTrucks()
    {
        return $this->where('Published', true)->orderBy('Rating', 'DESC')->findAll();
    }

}