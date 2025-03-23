<?php

namespace App\Models;

use CodeIgniter\Model;

class MediaModel extends Model
{
    protected $table = 'media';

    protected $allowedFields = [
        'FoodTruckName',
        'MenuName',
        'FileName',
        'FileType'
        ];
}