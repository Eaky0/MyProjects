import 'package:flutter/foundation.dart';
import 'Restaurant.dart';

class FavoritesState extends ChangeNotifier {
  Map<int, Restaurant> favorites = {};
  List<String> favoriteContacts = [];

  void toggleFavorite(Restaurant restaurant) {
    if (favorites.containsKey(restaurant.index)) {
      favorites.remove(restaurant.index);
    } else {
      favorites[restaurant.index] = restaurant;
    }
    notifyListeners();
  }

  void toggleFavoriteContact(String name) {
    if (favoriteContacts.contains(name)) {
      favoriteContacts.remove(name);
    } else {
      favoriteContacts.add(name);
    }
    notifyListeners();
  }
}
