function CheckValidation(event){
    event.preventDefault();

    const AlertSection = document.getElementById('AlertSection');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');

    const Email = document.getElementById("Email").value;
    const Message = document.getElementById("MsgText").value;

    //Email-address validation
    const Emailexp = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/
    if(!Email.match(Emailexp)){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Invalid E-mail address";
        AlertList.appendChild(Problem);
    }

    //Message text validation
    if(Message === ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Cannot sent a empty message";
        AlertList.appendChild(Problem);
    }

    if(AlertList.innerHTML !== ""){
        AlertMessage.appendChild(AlertList);
        AlertSection.appendChild(AlertMessage);
    }
    else{
        document.getElementById("ContactForm").submit();
    }


}