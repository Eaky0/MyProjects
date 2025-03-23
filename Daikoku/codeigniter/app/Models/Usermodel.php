<?php

namespace App\Models;

use CodeIgniter\Model;

class UserModel extends Model
{
    protected $table = 'users';

    protected $allowedFields = ['FirstName', 'LastName', 'BirthDate', 'NickName', 'Email', 'Password', 'UserType', 'ProfilePicture'];


    public function getUsers()
    {
        return $this->findAll();
    }



}