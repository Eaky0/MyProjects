import 'package:flutter/material.dart';
import 'Restaurant.dart';

class ActivityRestaurantPage extends StatefulWidget {
  final Restaurant restaurant;
  const ActivityRestaurantPage({Key? key, required this.restaurant}) : super(key: key);

  @override
  State<ActivityRestaurantPage> createState() => _ActivityRestaurantPage();
}

class _ActivityRestaurantPage extends State<ActivityRestaurantPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.white,
      body: SingleChildScrollView(
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            _buildImageWithText(context),
            Padding(
              padding: const EdgeInsets.all(40.0),
              child: Text(
                'Welcome to ${widget.restaurant.name}, a sparkling gem of a restaurant that opened its doors in 2013 and has since enchanted guests\' senses with its enchanting Mediterranean cuisine.\n\n${widget.restaurant.name}, which means \'radiant\' in Italian, embodies the warmth and vibrancy of the Mediterranean in every meal it serves. Located in the heart of Hasselt, the restaurant attracts guests with its elegant ambiance and refined dishes.\n\n${widget.restaurant.name}\'s cuisine is a celebration of the diverse culinary traditions of the Mediterranean, with dishes inspired by the flavors of Italy, Spain, Greece and other countries around the sea. Fresh ingredients are carefully selected and masterfully prepared by our talented chefs, who strive for perfection in every bite.\n\nWhether you enjoy a glass of sun-drenched wine on our attractive terrace or immerse yourself in the intimate atmosphere of our stylish interior, an unforgettable culinary experience is on the menu at ${widget.restaurant.name}.\n\nWhether it\'s a romantic dinner for two, a fun gathering with friends or a special occasion to celebrate, ${widget.restaurant.name} offers a welcoming and unforgettable experience for every occasion. Come and be enchanted by the brilliance of ${widget.restaurant.name}.',
                style: TextStyle(fontSize: 14),
              ),
            ),
            SizedBox(height: 50),
          ],
        ),
      ),
    );
  }

  Widget _buildImageWithText(BuildContext context) {
    return Stack(
      children: [
        Container(
          width: MediaQuery.of(context).size.width,
          height: 200.0,
          child: Image.asset(
            'assets/images/luminoso.jpg',
            fit: BoxFit.cover,
          ),
        ),
        Positioned(
          bottom: 20.0,
          left: 0.0,
          right: 0.0,
          child: Container(
            alignment: Alignment.center,
            decoration: BoxDecoration(
              color: Colors.black.withOpacity(0.5),
            ),
            child: Text(
              widget.restaurant.name,
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
}
