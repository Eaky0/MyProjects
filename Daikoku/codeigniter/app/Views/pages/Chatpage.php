<div id="HeaderSection" class="container">
  <div id="SectionText" class="row">
    <div class="col text-center">
      <h1 class="display-1">Chats</h1>
    </div>
  </div>
</div>



<div id="ChatSection" class="container p-4">
    <div class="row mx-auto bg-white">
        <div id="Contacts" class="col-4 bg-white px-0">
        <?php if(!empty($Contacts)): ?>
            <div class=" list-group list-group-flush h-100 p-0 overflow-y-auto">
                <div class="p-3 list-group-item">
                    <h2>Contacts</h2>
                </div>
                <?php foreach ($Contacts as $Contact): ?>
                    <?php if(session("UserType") == 'C'): ?>
                    <button id="<?= $Contact['ToUser'] ?>" type="button" class="p-3 list-group-item border list-group-item-action ContactText" style="word-wrap: break-word;" onclick="ViewChats('<?= $Contact['ToUser'] ?>')"><?= $Contact["ToUser"] ?></button>
                    <?php else: ?>
                    <button id="<?= $Contact['FromUser'] ?>" type="button" class="p-3 list-group-item border list-group-item-action" style="word-wrap: break-word;" onclick="ViewChats('<?= $Contact['FromUser'] ?>')"><?= $Contact["FromUser"] ?></button>                    
                    <?php endif ?>

                <?php endforeach ?>
            </div>
        <?php else: ?>
            <?php if(session("UserType") == "C"): ?>
            <h4>It seems like you have no chats at the moment, explore food truckers and start chatting with them!</h4>

            <?php else: ?>
            <h4>It seems like you have no chats at the moment, You'll have to wait until a client decides to text you!</h4>

            <?php endif ?>
        <?php endif ?>
        
        </div>
        <div id="MessageTerminal" class="col-8 border">
            <div class="row">
                <div id="ContactNameSection" class="col-12">
                    <!--
                    <div class=" list-group list-group-flush h-100 p-0 overflow-y-auto">
                        <div class="p-3 list-group-item">
                            <h2 id="ContactName">FryFrenzy</h2>
                        </div>
                    </div>
                    -->
                </div>
                <div id="Messages" class="bg-white col-12 overflow-y-auto text-center d-flex align-items-center justify-content-center">
                    <div id="ChatWindow" class="row">



                        <div class="col-12">
                            <img class="img-fluid h-75 w-50" src="<?= base_url("staticimg/ChatboxIcon.png") ?>" alt="Chatbox">
                            <h1>In order to chat, click on a contact</h1>
                        </div>

                        <!-- Date Tag example
                        <div class="col-12 text-center">
                            <div class="p">December 16th, 2023</div>
                        </div> -->

                        <!-- Message example from user
                        <div class="col-12 justify-content-end align-items-end d-flex">
                            <div class="w-lg-25 w-sm-50 p-2 m-2 rounded messageboxYou">
                                <div class="p fs-5">Hello</div>
                                <span class="badge-warning"><strong>12:30 PM</strong></span>
                            </div>
                        </div> -->
                        
                        <!-- Message example to user
                        <div class="col-12 justify-content-start align-items-start d-flex">
                            <div class="w-lg-25 w-sm-50 p-2 m-2 rounded messageboxThem">
                                <div class="p fs-5">Hi</div>
                                <span class="badge-warning"><strong>12:30 PM</strong></span>
                            </div>
                        </div> -->


                    </div>
                </div>
                <div id="InputSection" class="col-12">
                    <!-- 
                    <div class="row border bg-white">
                        <div class="col-lg-10 col-xs-12 py-3">
                            <textarea id="ContentText" oninput="CheckMsgButton()" placeholder="Hi!.." class="form-control w-100 h-100"style="resize: none;"></textarea>
                        </div>
                        <div class="col-lg-2 col-xs-12 justify-content-center d-flex align-items-center">
                            <button id="MsgButton" type="button" class="btn border-black bg-black btn-primary rounded-circle" disabled><i class="bi bi-send"></i></button>
                        </div>
                    </div>
                    -->
                </div>
            </div>
        </div>
    </div>
</div>

<script>
var headers = new Headers();
headers.append("Accept", "application/json");
headers.append('X-Requested-With', 'XMLHttpRequest');
headers.append('X-CSRF-TOKEN', '<?= csrf_hash() ?>');

</script>