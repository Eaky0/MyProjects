import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';
import 'restaurantInfo.dart';
import 'FavoritesState.dart';
import 'Restaurant.dart';
import 'package:provider/provider.dart';
import 'package:fluttertoast/fluttertoast.dart';

// ignore: camel_case_types
class home extends StatefulWidget {
  const home({required key});

  @override
  State<home> createState() => _HomeState();
}

class _HomeState extends State<home> {
  List<bool> _isFavoritedList = List.filled(20, false);
  int numFavoritesToShow = 5;

  void initState() {
    super.initState();
    Fluttertoast.showToast(
      msg: "Your limousine has departed",
      toastLength: Toast.LENGTH_SHORT,
      gravity: ToastGravity.TOP,
      timeInSecForIosWeb: 5,
      backgroundColor: Colors.blue.shade300,
      textColor: Colors.black,
      fontSize: 22.0,
    );
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        backgroundColor: Colors.white,
        body: Stack(
          children: [
            Column(
              mainAxisAlignment: MainAxisAlignment.start,
              children: <Widget>[
                _buildAppBar(),
              ],
            ),
            Positioned(
              top: 120.0,
              left: 0.0,
              right: 0.0,
              bottom: 0.0,
              child: SingleChildScrollView(
                child: Column(
                  children: [
                    _buildImageWithText(context),
                    SizedBox(height: 30),
                    _buildSuggestions(context),
                    SizedBox(height: 30),
                    _buildFavorites(context),
                    SizedBox(height: 60)
                  ],
                ),
              ),
            ),
          ],
        ),
        floatingActionButton: _buildActivityButton(),
        floatingActionButtonLocation: FloatingActionButtonLocation.endFloat,
      ),
    );
  }


  Widget _buildAppBar() {
    return Container(
      height: 120.0,
      alignment: Alignment.center,
      child: Text(
        '~ NOBU ~',
        style: TextStyle(
          fontFamily: 'Pilgrim',
          fontSize: 55.0,
        ),
      ),
    );
  }

  Widget _buildImageWithText(BuildContext context) {
    return Stack(
      children: [
        Container(
          width: 450.0,
          height: 500.0,
          child: Image.asset(
            'assets/images/limoinside.jpg',
            fit: BoxFit.cover,
          ),
        ),
        Positioned(
          bottom: 50.0,
          left: 0.0,
          right: 0.0,
          child: Container(
            alignment: Alignment.center,
            decoration: BoxDecoration(
              color: Colors.black.withOpacity(0.6),
            ),
            child: Text(
              'STEP INTO LUXURY',
              style: TextStyle(
                color: Colors.white,
                fontSize: 40.0,
              ),
            ),
          ),
        ),
      ],
    );
  }

  // Widget _buildButton(BuildContext context) {
  //   return Positioned(
  //     bottom: 20.0,
  //     left: 90.0,
  //     right: 90.0,
  //     child: GestureDetector(
  //       onTap: () {
  //         context.goNamed("Search");
  //       },
  //       child: Container(
  //         padding: EdgeInsets.all(2.0),
  //         decoration: BoxDecoration(
  //           color: Colors.white,
  //           borderRadius: BorderRadius.circular(5.0),
  //         ),
  //         child: Row(
  //           mainAxisAlignment: MainAxisAlignment.center,
  //           children: [
  //             Text(
  //               'TRY IT NOW',
  //               style: TextStyle(
  //                 color: Colors.black,
  //                 fontSize: 18.0,
  //               ),
  //             ),
  //             Icon(
  //               Icons.navigate_next,
  //               color: Colors.black,
  //             ),
  //           ],
  //         ),
  //       ),
  //     ),
  //   );
  // }

  Widget _buildSuggestions(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Padding(
          padding: EdgeInsets.symmetric(horizontal: 20.0),
          child: Text(
            'Suggestions',
            style: TextStyle(
              fontSize: 24.0,
              fontWeight: FontWeight.bold,
            ),
          ),
        ),
        SizedBox(
          height: 10.0,
        ),
        Container(
          height: 180.0,
          child: ListView(
            scrollDirection: Axis.horizontal,
            children: [
              _buildCarouselItem(context, new Restaurant(0, 'Luminoso', 'Mediterranean', 4.7)),
              _buildCarouselItem(context, new Restaurant(1, 'Item 2', 'Cuisine', 0.0)),
              _buildCarouselItem(context, new Restaurant(2, 'Item 3', 'Cuisine', 0.0)),
              _buildCarouselItem(context, new Restaurant(3, 'Item 4', 'Cuisine', 0.0)),
              _buildCarouselItem(context, new Restaurant(4, 'Item 5', 'Cuisine', 0.0)),
              _buildCarouselItem(context, new Restaurant(5, 'Item 6', 'Cuisine', 0.0)),
              _buildCarouselItem(context, new Restaurant(6, 'Item 7', 'Cuisine', 0.0)),
              _buildCarouselItem(context, new Restaurant(7, 'Item 8', 'Cuisine', 0.0)),
              _buildCarouselItem(context, new Restaurant(8, 'Item 9', 'Cuisine', 0.0)),
              _buildCarouselItem(context, new Restaurant(9, 'Item 10', 'Cuisine', 0.0)),
              _buildCarouselItem(context, new Restaurant(10, 'Item 11', 'Cuisine', 0.0)),

            ],
          ),
        ),
      ],
    );
  }

  Widget _buildCarouselItem(BuildContext context, Restaurant restaurant) {
    FavoritesState favoritesState = Provider.of<FavoritesState>(context);
    return GestureDetector(
      onTap: () {
        context.push(context.namedLocation("RestaurantInfo"));
      },
      child: Container(
      margin: EdgeInsets.symmetric(horizontal: 12.0),
      width: 230.0,
      decoration: BoxDecoration(
        color: Colors.grey[300],
        borderRadius: BorderRadius.circular(10.0),
      ),
      child: SingleChildScrollView(
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              ClipRRect(
                borderRadius: BorderRadius.circular(10.0),
                child: Image.asset(
                  'assets/images/luminoso.jpg',
                  width: 250.0,
                  height: 100.0,
                  fit: BoxFit.cover,
                ),
              ),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Padding(
                  padding: EdgeInsets.only(left: 10.0),
                  child: Text(
                    restaurant.name,
                    style: TextStyle(
                      fontSize: 16.0,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),
                Padding(
                  padding: EdgeInsets.only(right: 1.0),
                  child: IconButton(
                    onPressed: () {
                      setState(() {
                        favoritesState.toggleFavorite(restaurant);
                        final isFavorited = favoritesState.favorites.containsKey(restaurant.index);
                        _isFavoritedList[restaurant.index] = isFavorited;
                      });

                    },
                    icon: Icon(
                      _isFavoritedList[restaurant.index] ? Icons.favorite : Icons.favorite_border,
                      color: _isFavoritedList[restaurant.index] ? Colors.red : null,
                      size: 26.0,
                    ),
                  ),
                ),
              ],
            ),
            Padding(
              padding: EdgeInsets.only(left: 10.0),

              child: Row(
                children: [
                  Text(
                    '${restaurant.cuisine} - ',
                    style: TextStyle(
                      fontSize: 14.0,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                  Text(
                    '★ ${restaurant.rating}',
                    style: TextStyle(
                      fontSize: 14.0,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    ),
    );

  }

  Widget _buildFavorites(BuildContext context) {
    var favoritesState = context.watch<FavoritesState>();

    if (favoritesState.favorites.isEmpty) {
      return Container();
    }

    List<Restaurant> allFavorites = favoritesState.favorites.values.toList();
    List<Restaurant> favoritesToShow = allFavorites.take(numFavoritesToShow).toList();

    bool moreThanFiveFavorites = favoritesState.favorites.length > numFavoritesToShow;

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Padding(
          padding: EdgeInsets.symmetric(horizontal: 20.0),
          child: Text(
            'Your favorites',
            style: TextStyle(
              fontSize: 24.0,
              fontWeight: FontWeight.bold,
            ),
          ),
        ),
        SizedBox(
          height: 10.0,
        ),
        Container(
          height: 180.0,
          child: ListView(
            scrollDirection: Axis.horizontal,
            children: [
              for (Restaurant restaurant in favoritesToShow)
                _buildCarouselItem(context, restaurant),
              if (moreThanFiveFavorites)
                InkWell(
                  onTap: () {
                    setState(() {
                      numFavoritesToShow += 5;
                    });
                  },
                  child: Container(
                    width: 100.0,
                    decoration: BoxDecoration(
                      color: Colors.grey[300],
                      borderRadius: BorderRadius.circular(10.0),
                    ),
                    child: Stack(
                      alignment: Alignment.center,
                      children: [
                        Positioned(
                          top: 60,
                          child: Icon(
                            Icons.add_circle,
                            size: 30.0,
                            color: Colors.black,
                          ),
                        ),
                        Positioned(
                          bottom: 60,
                          child: Text(
                            'Show More',
                            style: TextStyle(
                              fontSize: 16.0,
                              fontWeight: FontWeight.bold,
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                ),
            ],
          ),
        ),
      ],
    );
  }

  Widget _buildActivityButton() {
    return FloatingActionButton(
      onPressed: () {
        context.push(context.namedLocation("ReservationsList"));
      },
      backgroundColor: Colors.blue.shade300,
      shape: CircleBorder(),
      child: Icon(Icons.restaurant),
    );
  }

}