<?php

use App\Controllers\ChatController;
use App\Controllers\ContactController;
use App\Controllers\FoodTruckEditor;
use App\Controllers\FoodTruckFilter;
use App\Controllers\FoodTruckInfo;
use App\Controllers\LoginChecker;
use App\Controllers\OrdersController;
use CodeIgniter\Router\RouteCollection;

/**
 * @var RouteCollection $routes
 */
//$routes->get('/', 'Home::index');

//use App\Controllers\News; 
use App\Controllers\Pages;
use App\Controllers\ProfileEditor;
use App\Controllers\ShoppingCartInfo;
use App\Controllers\SignUpChecker;

/*$routes->get('news', [News::class, 'index']);
$routes->get('news/new', [News::class, 'new']);
$routes->post('news', [News::class, 'create']);
$routes->get('news/(:segment)', [News::class, 'show']);*/

//Login & Signup controller routes
$routes->post('Login', [LoginChecker::class, 'loginUser']);
$routes->get('Logout', [LoginChecker::class, 'logoutUser']);

$routes->get('get-Users', 'SignUpChecker::getUsers');
$routes->get('get-FoodTrucks', 'SignUpChecker::getFoodTrucks');
$routes->post("SignUp/SignedUp", [SignUpChecker::class, 'MakeUser']);

//FoodTruck Editor Controller routes
$routes->post('Foodtruckeditorpage/AddedMainImages', [FoodTruckEditor::class, 'AddMainImageEditor']);
$routes->post('Foodtruckeditorpage/DeleteMainImage', [FoodTruckEditor::class, 'DeleteMainImageEditor']);
$routes->post('Foodtruckeditorpage/AddedCategory', [FoodTruckEditor::class, 'NewCategoryEditor']);
$routes->post('Foodtruckeditorpage/DeleteCategory', [FoodTruckEditor::class, 'DeleteCategoryEditor']);
$routes->post('Foodtruckeditorpage/AddedProduct', [FoodTruckEditor::class, 'NewProductEditor']);
$routes->post('Foodtruckeditorpage/DeleteImagesVideos', [FoodTruckEditor::class, 'DeleteIVEditor']);
$routes->post('Foodtruckeditorpage/DeleteProduct', [FoodTruckEditor::class, 'DeleteProductEditor']);
$routes->post('Foodtruckeditorpage/AddedImagesVideos', [FoodTruckEditor::class, 'addIVEditor']);
$routes->post('Foodtruckeditorpage/DeleteImagesVideos', [FoodTruckEditor::class, 'DeleteIVEditor']);
$routes->post('Foodtruckeditorpage/EditedMainSection', [FoodTruckEditor::class, 'EditMainEditor']);
$routes->post('Foodtruckeditorpage/EditedContactSection', [FoodTruckEditor::class, 'EditContactEditor']);
$routes->post('Foodtruckeditorpage/EditedMenuInfo', [FoodTruckEditor::class, 'EditMenuEditor']);
$routes->get('Foodtruckeditorpage', [FoodTruckEditor::class, 'FTeditor']);

//FoodTruck Filter controller routes
$routes->get('Foodtruckspage', [FoodTruckFilter::class, 'FoodTrucks']);
$routes->get('load-food-trucks', 'FoodTruckFilter::LoadFoodTrucks');
$routes->post('filter-foodtrucks', 'FoodTruckFilter::Filter');
$routes->post('search-foodtrucks', 'FoodTruckFilter::Search');

//FoodTruck Information controller routes
$routes->post('Foodtruckinfopage/(:segment)/ReviewWritten', [FoodTruckInfo::class, 'WriteReview']);
$routes->get('Foodtruckinfopage/(:segment)', [FoodTruckInfo::class, 'LoadInfo']);
$routes->get('get-menus', 'FoodTruckInfo::getMenus');

//Profile page editor controller routes
$routes->post('Profilepage/ProfileEdited', 'ProfileEditor::editProfile');
$routes->get('Profilepage', 'ProfileEditor::LoadProfile');
$routes->post("Profilepage/ProfilePictureChanged", 'ProfileEditor::editProfilePicture');

//Shopping cart information controller routes:
$routes->get("Shoppingcart", [ShoppingCartInfo::class, 'LoadCart']);
$routes->post("Shoppingcart/ChangedAmount", [ShoppingCartInfo::class, 'ChangeAmount']);
$routes->post("Shoppingcart/DeletedFromCart", [ShoppingCartInfo::class, 'DeleteFromCart']);
$routes->post("Foodtruckinfopage/(:segment)/AddedToShoppingCart", [ShoppingCartInfo::class, 'AddProduct']);

//Chat Controller routes:
$routes->get("Chatpage", [ChatController::class, 'LoadChats']);
$routes->get("Chatpage/(:segment)", [ChatController::class, 'newChat']);
$routes->post("view-chats", [ChatController::class, 'ViewChatWindow']);
$routes->post("send-chat", [ChatController::class, 'SendChat']);

//Orders Controller routes:
$routes->get("Orders", [OrdersController::class,'LoadOrders']);
$routes->post("ShoppingCart/ConfirmOrder", [OrdersController::class, 'ConfirmOrder']);
$routes->post("Orders/OrderSettingsChanged/(:segment)", [OrdersController::class, 'ChangeOrderSettings']);
$routes->post("Orders/PickUpOrder", [OrdersController::class, 'PickUpOrder']);
$routes->get("Orders/PickUpOrder/(:segment)", [OrdersController::class, 'PickUpOrder']);
$routes->get("Orders/OrderReview/(:segment)", [OrdersController::class, 'ReviewOrder']);
$routes->post('OrderReview/(:segment)/(:segment)/ReviewWritten', [OrdersController::class, 'WriteOrderReview']);

//Contact controller routes
$routes->post("Contactpage/MessageSent",  [ContactController::class, 'SendMessage']);

//Standard pages controller routes
$routes->get('/', [Pages::class, 'main']);
$routes->get('Mainpage', [Pages::class, 'main']);
$routes->get('EventInfopage/(:segment)/(:segment)', [Pages::class, 'showEvent']);
$routes->get('Eventspage', [Pages::class, 'events']);

$routes->get('(:segment)', [Pages::class, 'view']);