function ChangeAmount($index){
    document.getElementById("AmountForm" + $index).submit();
}

function CheckFoodTruck(event){
    event.preventDefault();
    const EncodedCart = document.getElementById("Products").value;
    const ShoppingCart = JSON.parse(EncodedCart);
    
    var PrevFoodTruck = null;

    const Alert = document.createElement("div");
    Alert.classList.add("alert", "alert-danger","text-center");

    ShoppingCart.forEach(Product => {
        if (PrevFoodTruck == null){
            PrevFoodTruck = Product.FoodTruckName;
        }

        if (PrevFoodTruck != Product["FoodTruckName"]){
            Alert.innerHTML = "To order, you need to place products of only 1 foodtruck in your shopping cart!"
            const AlertSection = document.getElementById("AlertSection");
            AlertSection.appendChild(Alert);
            return;
        }
    });    

    if (Alert.innerHTML == ""){
        document.getElementById("ConfirmationForm").submit();
    }
}