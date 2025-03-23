CurrentContact = null;

function reloadChat(){
    if (CurrentContact != null){
        ContactInfo = {}
        ContactInfo["Name"] = CurrentContact;

        fetch("http://localhost:8080/view-chats",{
            credentials: 'include',
            method: 'POST',
            headers: headers,
            body: JSON.stringify(ContactInfo)
        })
        .then(response => response.json())
        .then(data => {
            headers.set('X-CSRF-TOKEN', data.newCSRFtoken);

            //RELOADING MESSAGES

            const Window = document.getElementById("ChatWindow");
            const MessagesSection = document.getElementById("Messages");
            Window.innerHTML = "";
            previousChatDate = null;


            data.Chats.forEach(Chat => {
                const Dateoptions = { year: 'numeric', month: 'long', day: 'numeric' };
                const Timestamp = new Date(Chat.Timestamp);
                const formattedDate = Timestamp.toLocaleDateString('en-US', Dateoptions);

                if (previousChatDate == null || previousChatDate != formattedDate){
                    const DateTag = document.createElement('div');
                    DateTag.classList.add("col-12", "text-center");
                    
                    const DateString = document.createElement('div');
                    DateString.classList.add("p");

                    DateString.innerHTML = formattedDate;
                    DateTag.appendChild(DateString);
                    Window.appendChild(DateTag);

                    previousChatDate = formattedDate;
                }

                if (Chat.ToUser == data.Name){
                    const MsgTo = document.createElement("div");
                    MsgTo.classList.add("col-12", "justify-content-end", "align-items-end", "d-flex");

                    const MsgBox = document.createElement("div");
                    MsgBox.classList.add("w-lg-25", "w-sm-50", "p-2", "rounded", "messageboxYou");

                    const MsgContent = document.createElement("div");
                    MsgContent.classList.add("p", "fs-5");
                    MsgContent.innerHTML = Chat.Content;

                    const MsgTime = document.createElement("span");
                    MsgTime.classList.add("badge-warning");

                    const Strong = document.createElement("strong");

                    const Timeoptions = { hour: '2-digit', minute: '2-digit' };
                    const formattedTime = Timestamp.toLocaleTimeString('en-US', Timeoptions);

                    Strong.innerHTML = formattedTime;

                    MsgTime.appendChild(Strong);

                    MsgBox.appendChild(MsgContent);
                    MsgBox.appendChild(MsgTime);
                    MsgTo.appendChild(MsgBox);
                    Window.appendChild(MsgTo);


                }
                else{
                    const MsgFrom = document.createElement("div");
                    MsgFrom.classList.add("col-12", "justify-content-start", "align-items-start", "d-flex");

                    const MsgBox = document.createElement("div");
                    MsgBox.classList.add("w-lg-25", "w-sm-50", "p-2", "rounded", "messageboxThem");

                    const MsgContent = document.createElement("div");
                    MsgContent.classList.add("p","fs-5");
                    MsgContent.innerHTML = Chat.Content;

                    const MsgTime = document.createElement("span");
                    MsgTime.classList.add("badge-warning");

                    const Strong = document.createElement("strong");

                    const Timeoptions = { hour: '2-digit', minute: '2-digit' };
                    const formattedTime = Timestamp.toLocaleTimeString('en-US', Timeoptions);

                    Strong.innerHTML = formattedTime;

                    MsgTime.appendChild(Strong);

                    MsgBox.appendChild(MsgContent);
                    MsgBox.appendChild(MsgTime);
                    MsgFrom.appendChild(MsgBox);
                    Window.appendChild(MsgFrom);



                }
            });

    })
    .catch(error => {
        console.error('Error:', error);
    });

    }
}

setInterval(reloadChat, 5000);



function ViewChats(Contact){

    ContactInfo = {}

    CurrentContact = Contact;

    ContactInfo["Name"] = Contact


    fetch("http://localhost:8080/view-chats",{
        credentials: 'include',
        method: 'POST',
        headers: headers,
        body: JSON.stringify(ContactInfo)
    })
    .then(response => response.json())
    .then(data => {
        console.log('Contacts', data);
        headers.set('X-CSRF-TOKEN', data.newCSRFtoken);

        //ADDING CONTACT NAME
        const ContactNameSection = document.getElementById("ContactNameSection");
        ContactNameSection.style.borderBottom = "solid 2px grey";

        ContactNameSection.innerHTML = "";

        const contactButtons = document.querySelectorAll('#Contacts button');
        contactButtons.forEach(button => {
            button.classList.remove('disabled');
        });

        //Don't allow to click twice on a contact:
        const ClickedContactButton = document.getElementById(data.Name);
        ClickedContactButton.classList.add('disabled');

        const listGroup = document.createElement('div');
        listGroup.classList.add('list-group', 'list-group-flush');
        
        const listItem = document.createElement('div');
        listItem.classList.add('list-group-item', 'mt-3');
    
        const heading = document.createElement('h2');
        heading.textContent = data.Name;
        heading.id = "ContactName";
    
        listItem.appendChild(heading);
        listGroup.appendChild(listItem);
        ContactNameSection.appendChild(listGroup);

        //ADDING MESSAGES

        const Window = document.getElementById("ChatWindow");
        const MessagesSection = document.getElementById("Messages");
        MessagesSection.classList.remove("d-flex", "text-center", "align-items", "justify-content-center");
        Window.innerHTML = "";
        previousChatDate = null;


        data.Chats.forEach(Chat => {
            const Dateoptions = { year: 'numeric', month: 'long', day: 'numeric' };
            const Timestamp = new Date(Chat.Timestamp);
            const formattedDate = Timestamp.toLocaleDateString('en-US', Dateoptions);

            if (previousChatDate == null || previousChatDate != formattedDate){
                const DateTag = document.createElement('div');
                DateTag.classList.add("col-12", "text-center");
                
                const DateString = document.createElement('div');
                DateString.classList.add("p");

                DateString.innerHTML = formattedDate;
                DateTag.appendChild(DateString);
                Window.appendChild(DateTag);

                previousChatDate = formattedDate;
            }

            if (Chat.ToUser == data.Name){
                const MsgTo = document.createElement("div");
                MsgTo.classList.add("col-12", "justify-content-end", "align-items-end", "d-flex");

                const MsgBox = document.createElement("div");
                MsgBox.classList.add("w-lg-25", "w-sm-50", "p-2", "rounded", "messageboxYou");

                const MsgContent = document.createElement("div");
                MsgContent.classList.add("p", "fs-5");
                MsgContent.innerHTML = Chat.Content;

                const MsgTime = document.createElement("span");
                MsgTime.classList.add("badge-warning");

                const Strong = document.createElement("strong");

                const Timeoptions = { hour: '2-digit', minute: '2-digit' };
                const formattedTime = Timestamp.toLocaleTimeString('en-US', Timeoptions);

                Strong.innerHTML = formattedTime;

                MsgTime.appendChild(Strong);

                MsgBox.appendChild(MsgContent);
                MsgBox.appendChild(MsgTime);
                MsgTo.appendChild(MsgBox);
                Window.appendChild(MsgTo);


            }
            else{
                const MsgFrom = document.createElement("div");
                MsgFrom.classList.add("col-12", "justify-content-start", "align-items-start", "d-flex");

                const MsgBox = document.createElement("div");
                MsgBox.classList.add("w-lg-25", "w-sm-50", "p-2", "rounded", "messageboxThem");

                const MsgContent = document.createElement("div");
                MsgContent.classList.add("p","fs-5");
                MsgContent.innerHTML = Chat.Content;

                const MsgTime = document.createElement("span");
                MsgTime.classList.add("badge-warning");

                const Strong = document.createElement("strong");

                const Timeoptions = { hour: '2-digit', minute: '2-digit' };
                const formattedTime = Timestamp.toLocaleTimeString('en-US', Timeoptions);

                Strong.innerHTML = formattedTime;

                MsgTime.appendChild(Strong);

                MsgBox.appendChild(MsgContent);
                MsgBox.appendChild(MsgTime);
                MsgFrom.appendChild(MsgBox);
                Window.appendChild(MsgFrom);



            }
        });

        //ADDING TEXTING SECTION

        const InputSection = document.getElementById("InputSection");
        InputSection.style.borderTop = "solid 2px grey";
        InputSection.innerHTML = "";

        const InputPanel = document.createElement("div");
        InputPanel.classList.add("row", "bg-white");

        const InputColumn = document.createElement("div");
        InputColumn.classList.add("col-lg-12", "col-xs-12", "py-3");            


        const InputGroup = document.createElement("div");
        InputGroup.classList.add("input-group");

        const ContentText = document.createElement("textarea");
        ContentText.id = "ContentText";
        ContentText.setAttribute('oninput', 'CheckMsgButton()');
        ContentText.placeholder = "Send a message...";
        ContentText.classList.add("form-control");
        ContentText.style.resize = 'none';

        const MsgButton = document.createElement("button");
        MsgButton.id = "MsgButton";
        MsgButton.setAttribute('onclick', 'sendChat()');
        MsgButton.setAttribute('disabled', 'true');
        MsgButton.classList.add("btn", "border-black", "bg-black", "btn-primary");
        MsgButton.type = 'button';

        const MsgIcon = document.createElement("i");
        MsgIcon.classList.add("bi", "bi-send");

        MsgButton.appendChild(MsgIcon);

        InputGroup.appendChild(ContentText);
        InputGroup.appendChild(MsgButton);

        InputColumn.appendChild(InputGroup);

        InputPanel.appendChild(InputColumn);

        InputSection.appendChild(InputPanel);

        MessagesSection.scrollTop = MessagesSection.scrollHeight;



    })
    .catch(error => {
        console.error('Error:', error);
    });


}

function CheckMsgButton(){
    const MsgButton = document.getElementById("MsgButton");
    const ContentText = document.getElementById("ContentText");

    if (ContentText.value == ""){
        MsgButton.setAttribute('disabled', 'true');
    }
    else{
        MsgButton.removeAttribute("disabled");
    }
    
}


function sendChat(){
    const Content = document.getElementById("ContentText");
    const Heading = document.getElementById("ContactName");

    SentTo = Heading.innerHTML;

    ContactInfo = {};
    ContactInfo["Name"] = SentTo;
    ContactInfo["Content"] = Content.value;


    fetch("http://localhost:8080/send-chat",{
        credentials: 'include',
        method: 'POST',
        headers: headers,
        body: JSON.stringify(ContactInfo)
    })
    .then(response => response.json())
    .then(data => {
        console.log('New Chat', data.NewChat);
        headers.set('X-CSRF-TOKEN', data.newCSRFtoken);

        ViewChats(ContactInfo["Name"]);


    })
    .catch(error => {
        console.error('Error:', error);
    });

}