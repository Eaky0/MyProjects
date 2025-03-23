document.getElementById("CancelButton").addEventListener("click", function(){
    document.getElementById("PfpForm").reset();
    const AlertSection = document.getElementById('AlertSection');
    AlertSection.innerHTML = "";
})


function CheckFile(event){
    event.preventDefault();
    const NewPfpInput = document.getElementById("Pfp");
    const Image = NewPfpInput.files[0];

    const AlertSection = document.getElementById('AlertSection');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');

    if (!Image){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Please select an image";
        AlertList.appendChild(Problem);
    }
    else{
        const ImageBytes = Image.size;
        const MBLimit = 20;
        const ByteLimit = MBLimit * (1024**2);

        if (ImageBytes > ByteLimit){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Size of image is too large (Limit = 20 MB)";
            AlertList.appendChild(Problem);
        }
    
    }

    if(AlertList.innerHTML !== ""){
        AlertMessage.appendChild(AlertList);
        AlertSection.appendChild(AlertMessage);
    }
    else{
        document.getElementById("PfpForm").submit();
    }
}


function CheckSettings(event){
    event.preventDefault();

    const FirstName = document.getElementById("Fname").value;
    const LastName = document.getElementById("Lname").value;
    const BirthDate = document.getElementById("Date").value;
    const Password = document.getElementById("Password").value;


    const AlertSection = document.getElementById('AlertSection2');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');


    //First & Last name validation

    if (FirstName == ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "First name is required";
        AlertList.appendChild(Problem);
    }

    if (LastName == ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Surname is required";
        AlertList.appendChild(Problem);
    }


    //Date of birth validation
    if (BirthDate == ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Date of birth is required";
        AlertList.appendChild(Problem);
    }

    //Password validation
    if(Password.length < 5){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Password must consist of at least 5 letters";
        AlertList.appendChild(Problem);
    }


    if(AlertList.innerHTML !== ""){
        AlertMessage.appendChild(AlertList);
        AlertSection.appendChild(AlertMessage);
    }
    else{
        document.getElementById("PfSettingsForm").submit();
    }



}