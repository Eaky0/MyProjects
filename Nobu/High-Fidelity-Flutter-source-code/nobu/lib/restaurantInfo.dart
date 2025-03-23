import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:carousel_slider/carousel_slider.dart';
import 'package:nobu/reservation.dart';

class restaurantInfo extends StatefulWidget {
  final String restaurantName;
  final String cuisine;
  final double rating;

  restaurantInfo({required this.restaurantName, required this.cuisine, required this.rating, required key});

  @override
  State<restaurantInfo> createState() => _RestaurantInfoState(restaurantName, cuisine, rating);
}

class _RestaurantInfoState extends State<restaurantInfo> {
   
   
 _RestaurantInfoState(String r_Name, String r_Cuisine, double r_Rating){
    Name = r_Name;
    Cuisine = r_Cuisine;
    Rating = r_Rating;
  }
  
  int _current = 0;

  get restaurantName => null;

  String Name = "";
  String Cuisine = "";
  double Rating = 0.0;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Stack(
        children: [
          Column(
            mainAxisAlignment: MainAxisAlignment.start,
            children: <Widget>[
              _buildAppBar(context),
            ],
          ),
          Positioned(
            top: 100.0,
            left: 0.0,
            right: 0.0,
            bottom: 0.0,
            child: SingleChildScrollView(
              child: Column(
                children: [
                  _buildImageWithText(),
                  SizedBox(height: 10),
                  _buildMainPage(context,)
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildAppBar(BuildContext context) {
    return AppBar(
      leading: IconButton(
        icon: Icon(Icons.navigate_before),
        onPressed: () {
          Navigator.pop(context);
        },
        iconSize: 50.0,
      ),
      title: Text(
        '~ NOBU ~',
        style: TextStyle(
          fontFamily: 'Pilgrim',
          fontSize: 55.0,
        ),
      ),
      centerTitle: true,
    );
  }

  Widget _buildImageWithText() {
    return Stack(
      children: [
        Container(
          width: 450.0,
          height: 300.0,
          child: Image.asset(
            'assets/images/luminoso.jpg',
            fit: BoxFit.cover,
          ),
        ),
        Positioned(
          bottom: 40.0,
          left: 0.0,
          right: 0.0,
          child: Container(
            alignment: Alignment.center,
            decoration: BoxDecoration(
              color: Colors.black.withOpacity(0.6),
            ),
            child: Text(
              Name,
              style: TextStyle(
                color: Colors.white,
                fontSize: 30.0,
              ),
            ),
          ),
        ),
      ],
    );
  }

  Widget _buildMainPage(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.all(20.0),
      child: Stack(
        children: [
          Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              SizedBox(height: 10),
              Text(
                Cuisine,
                style: TextStyle(fontSize: 18, fontStyle: FontStyle.italic),
              ),
              SizedBox(height: 50),
              CarouselSlider(
                options: CarouselOptions(
                  height: 200.0,
                  enlargeCenterPage: true,
                  onPageChanged: (index, reason) {
                    setState(() {
                      _current = index;
                    });
                  },
                ),
                items: [
                  Image.asset('assets/images/food1.jpg', fit: BoxFit.cover),
                  Image.asset('assets/images/food2.jpg', fit: BoxFit.cover),
                  Image.asset('assets/images/food3.jpg', fit: BoxFit.cover),
                ],
              ),
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: List.generate(
                  3,
                      (index) {
                    return Container(
                      width: 8.0,
                      height: 8.0,
                      margin: EdgeInsets.symmetric(vertical: 10.0, horizontal: 2.0),
                      decoration: BoxDecoration(
                        shape: BoxShape.circle,
                        color: _current == index
                            ? Colors.black
                            : Colors.grey,
                      ),
                    );
                  },
                ),
              ),
              SizedBox(height: 20),
              Row(
                children: [
                  Icon(Icons.place),
                  SizedBox(width: 10),
                  Text(
                    '123 Main Street, City, Country',
                    style: TextStyle(fontSize: 18),
                  ),
                ],
              ),
              SizedBox(height: 10),
              Row(
                children: [
                  Icon(Icons.phone),
                  SizedBox(width: 10),
                  Text(
                    '+32 12 23 34 45',
                    style: TextStyle(fontSize: 18),
                  ),
                ],
              ),
            ],
          ),
          Positioned(
            top: 0,
            right: 0,
            child: ElevatedButton(
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(
                    builder: (context) => Reservation(restaurantName: Name),
                  ),
                );
              },
              child: Text('BOOK NOW'),
            ),
          ),
        ],
      ),
    );
  }
}