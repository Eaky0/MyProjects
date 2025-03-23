function CheckReview(Product, event){

    event.preventDefault();

    const ReviewText = document.getElementById("ReviewText" + Product);
    const Rating = document.getElementById("Rating" + Product);
    const AlertSection = document.getElementById("AlertSection" + Product);    
    AlertSection.innerHTML = "";

    const Alert = document.createElement("div");
    Alert.classList.add("alert", "alert-danger");

    const AlertList = document.createElement("ul");

    if (ReviewText.value == ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "No review written."
        AlertList.appendChild(Problem);
    }

    if (Rating.value === "" || Rating.selectedOptions[0].label === "No Rating"){
        const Problem = document.createElement("li");
        Problem.innerHTML = "No rating given."
        AlertList.appendChild(Problem);
    }

    if (AlertList.innerHTML === ""){
        document.getElementById("ReviewForm" + Product).submit();
    }
    else{
        Alert.appendChild(AlertList);
        AlertSection.appendChild(Alert);
    }

}