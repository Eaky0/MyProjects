<?php

namespace App\Models;

use CodeIgniter\Model;

class ChatModel extends Model
{
    protected $table = 'chats';
    protected $allowedFields = ['FromUser', 'ToUser', 'Timestamp', 'Content', 'Status'];

}

