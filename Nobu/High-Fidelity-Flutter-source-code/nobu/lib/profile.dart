import 'package:flutter/material.dart';
import 'package:nobu/FavoritesState.dart';
import 'package:provider/provider.dart';
import 'package:go_router/go_router.dart';
import 'Restaurant.dart';
import 'restaurantInfo.dart';
import 'Booking.dart';
import 'package:faker/faker.dart';
import 'dart:math';

// ignore: use_key_in_widget_constructors, camel_case_types
class ProfilePage extends StatefulWidget {

  const ProfilePage({required key});

  @override
  State<ProfilePage> createState() => _profileState();
}

class _profileState extends State<ProfilePage> {

  bool _isProfileSettingsExpanded = false;
  bool _isContactInfoExpanded = false;
  bool _isPaymentDetailsExpanded = false;
  final Faker _faker = Faker();
  final Random _random = Random();

  @override
  Widget build(BuildContext context) {
    return Scaffold(

      body: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Container(
            padding: EdgeInsets.all(16.0),
            color: Colors.white.withOpacity(0.5),
            child: Row(
              children: [
                CircleAvatar(
                  radius: 60,
                  backgroundImage: AssetImage('assets/images/kristel_verbeke.jpeg'),
                ),
                SizedBox(width: 16.0),
                Text(
                  'Kristel Verbeke',
                  style: TextStyle(
                    fontSize: 32.0,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ],
            ),
          ),
          Divider(color: Colors.black),
          DefaultTabController(
            length: 4,
            child: Column(
              children: [
                TabBar(
                  tabs: [
                    _buildTabWithIcon('User Info', Icons.person),
                    _buildTabWithIcon('Favorites', Icons.favorite),
                    _buildTabWithIcon('History', Icons.history),
                    _buildTabWithIcon('Contacts', Icons.group),
                  ],
                  labelColor: Colors.blue.shade300,
                  indicatorColor: Colors.blue.shade300,
                ),
                SizedBox(
                  height: MediaQuery.of(context).size.height - AppBar().preferredSize.height - 240,
                  child: TabBarView(
                    children: [
                      _buildUserInfoTab(),
                      _buildFavoritesTab(),
                      _buildHistoryTab(),
                      _buildCompanionsTab(),
                    ],
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildUserInfoTab() {
    return ListView(
      padding: EdgeInsets.all(16.0),
      children: [
        Card(
          elevation: 4.0,
          margin: EdgeInsets.symmetric(vertical: 8.0),
          color: Colors.blue.shade50,
          child: ListTile(
            title: Text(
              'Profile Settings',
              style: TextStyle(fontSize: 18.0, fontWeight: FontWeight.bold),
            ),
            onTap: () {
              setState(() {
                _isProfileSettingsExpanded = !_isProfileSettingsExpanded;
              });
            },
            trailing: Icon(_isProfileSettingsExpanded ? Icons.expand_less : Icons.expand_more),
          ),
        ),
        if (_isProfileSettingsExpanded) ...[
          SizedBox(height: 8),
          Container(
            padding: EdgeInsets.all(16.0),
            decoration: BoxDecoration(
              border: Border.all(color: Colors.blue.shade100),
              borderRadius: BorderRadius.circular(8.0),
            ),
            child: Stack(
              children: [
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      'Username: Kristel Verbeke',
                      style: TextStyle(fontSize: 16.0),
                    ),
                    SizedBox(height: 8),
                    Text(
                      'Full Name: Kristel Verbeke',
                      style: TextStyle(fontSize: 16.0),
                    ),
                    SizedBox(height: 8),
                    Text(
                      'Date of Birth: 10/12/1975',
                      style: TextStyle(fontSize: 16.0),
                    ),
                  ],
                ),
                Positioned(
                  top: -15,
                  right: -15,
                  child: IconButton(
                    icon: Icon(Icons.edit),
                    onPressed: () {},
                  ),
                ),
              ],
            ),
          ),
        ],
        Card(
          elevation: 4.0,
          margin: EdgeInsets.symmetric(vertical: 8.0),
          color: Colors.blue.shade50,
          child: ListTile(
            title: Text(
              'Contact Information',
              style: TextStyle(fontSize: 18.0, fontWeight: FontWeight.bold),
            ),
            onTap: () {
              setState(() {
                _isContactInfoExpanded = !_isContactInfoExpanded;
              });
            },
            trailing: Icon(_isContactInfoExpanded ? Icons.expand_less : Icons.expand_more),
          ),
        ),
        if (_isContactInfoExpanded) ...[
          SizedBox(height: 8),
          Container(
            padding: EdgeInsets.all(16.0),
            decoration: BoxDecoration(
              border: Border.all(color: Colors.blue.shade100),
              borderRadius: BorderRadius.circular(8.0),
            ),
            child: Stack(
              children: [
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      'Mail: kristel.verbeke@gmail.com',
                      style: TextStyle(fontSize: 16.0),
                    ),
                    SizedBox(height: 8),
                    Text(
                      'Phone: +32 412 23 34 45',
                      style: TextStyle(fontSize: 16.0),
                    ),
                    SizedBox(height: 8),
                    Text(
                      'Address: Dorpstraat 12 , Hamme, Belgium',
                      style: TextStyle(fontSize: 16.0),
                    ),
                  ],
                ),
                Positioned(
                  top: -15,
                  right: -15,
                  child: IconButton(
                    icon: Icon(Icons.edit),
                    onPressed: () {},
                  ),
                ),
              ],
            ),
          ),
        ],
        Card(
          elevation: 4.0,
          margin: EdgeInsets.symmetric(vertical: 8.0),
          color: Colors.blue.shade50,
          child: ListTile(
            title: Text(
              'Payment Details',
              style: TextStyle(fontSize: 18.0, fontWeight: FontWeight.bold),
            ),
            onTap: () {
              setState(() {
                _isPaymentDetailsExpanded = !_isPaymentDetailsExpanded;
              });
            },
            trailing: Icon(_isPaymentDetailsExpanded ? Icons.expand_less : Icons.expand_more),
          ),
        ),
        if (_isPaymentDetailsExpanded) ...[
          SizedBox(height: 8),
          Container(
            padding: EdgeInsets.all(16.0),
            decoration: BoxDecoration(
              border: Border.all(color: Colors.blue.shade100),
              borderRadius: BorderRadius.circular(8.0),
            ),
            child: Stack(
              children: [
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      'Card Number: **** **** **** 1234',
                      style: TextStyle(fontSize: 16.0),
                    ),
                    SizedBox(height: 8),
                    Text(
                      'Expiration Date: 12/24',
                      style: TextStyle(fontSize: 16.0),
                    ),
                    SizedBox(height: 8),
                    Text(
                      'Billing Address: Dorpstraat 12 , Hamme, Belgium',
                      style: TextStyle(fontSize: 16.0),
                    ),
                  ],
                ),
                Positioned(
                  top: -15,
                  right: -15,
                  child: IconButton(
                    icon: Icon(Icons.edit),
                    onPressed: () {},
                  ),
                ),
              ],
            ),
          ),
        ],
      ],
    );
  }

  Widget _buildFavoritesTab() {
    var favoritesState = context.watch<FavoritesState>();

    return favoritesState.favorites.isEmpty
        ? Center(
      child: Text('You have no favorites'),
    )
        : GridView.count(
      crossAxisCount: 2,
      children: favoritesState.favorites.values.map((restaurant) {
        return Card(
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              Image.asset(
                'assets/images/luminoso.jpg',
                fit: BoxFit.cover,
                height: 110,
              ),
              ListTile(
                title: Text(
                  restaurant.name ?? '',
                  style: TextStyle(
                    fontSize: 16,
                    fontWeight: FontWeight.bold,
                  ),
                ),
                subtitle: Text(
                  restaurant.cuisine ?? '',
                  style: TextStyle(
                    fontSize: 12,
                    fontWeight: FontWeight.bold,
                  ),
                ),
                trailing: Text(
                  restaurant.rating?.toString() ?? '',
                  style: TextStyle(
                    fontSize: 16,
                  ),
                ),
                onTap: () {
                  context.push(context.namedLocation("RestaurantInfo"));
                },
              ),
            ],
          ),
        );
      }).toList(),
    );
  }


  Widget _buildHistoryTab() {
    List<Booking> reservations = List.generate(
      5,
          (index) {
        List<String> statuses = ['Confirmed', 'Completed', 'Review Given'];
        String status = statuses[Random().nextInt(statuses.length)];

        String review = status == 'Review Given' ? _faker.lorem.sentences(3).join(' ') : '';
        int rating = status == 'Review Given' ? Random().nextInt(5) + 1 : 0;

        return Booking(
          restaurantName: _faker.food.restaurant(),
          date: DateTime.now().add(Duration(days: index)),
          time: TimeOfDay(hour: Random().nextInt(24), minute: Random().nextInt(60)),
          partySize: Random().nextInt(10) + 1,
          hasLimousine: Random().nextBool(),
          contacts: [_faker.person.name(), _faker.person.name(), _faker.person.name()],
          review: review,
          status: status,
          rating: rating,
        );
      },
    );

    return ListView.builder(
      itemCount: reservations.length,
      itemBuilder: (context, index) {
        return Card(
          margin: EdgeInsets.all(8.0),
          child: ExpansionTile(
            title: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(reservations[index].restaurantName),
                Text('Status: ${reservations[index].status}'),
              ],
            ),
            subtitle: Text(
                '${reservations[index].date.toString().split(' ')[0]} | ${reservations[index].time.format(context)}'),
            children: [
              Row(
                children: [
                  Expanded(
                    child: SizedBox(
                      height: 150,
                      child: Image.asset(
                        'assets/images/luminoso.jpg',
                        fit: BoxFit.cover,
                      ),
                    ),
                  ),
                ],
              ),
              ListTile(
                title: Text('Date: ${reservations[index].date.toString().split(' ')[0]}'),
              ),
              ListTile(
                title: Text('Time: ${reservations[index].time.format(context)}'),
              ),
              ListTile(
                title: Text('Party Size: ${reservations[index].partySize}'),
              ),
              ListTile(
                title: Text('Limousine: ${reservations[index].hasLimousine ? 'Yes' : 'No'}'),
              ),
              ListTile(
                title: Text('Contacts: ${reservations[index].contacts.join(', ')}'),
              ),
              if (reservations[index].status == 'Completed') ...[
                ElevatedButton(
                  onPressed: () {
                    showModalBottomSheet(
                      context: context,
                      builder: (context) {
                        return StatefulBuilder(
                          builder: (context, setState) {
                            return Container(
                              padding: EdgeInsets.all(20.0),
                              child: Column(
                                mainAxisSize: MainAxisSize.min,
                                children: [
                                  TextField(
                                    decoration: InputDecoration(
                                      hintText: 'Enter your review...',
                                      border: OutlineInputBorder(),
                                    ),
                                    maxLines: 3,
                                  ),
                                  SizedBox(height: 20.0),
                                  Row(
                                    mainAxisAlignment: MainAxisAlignment.center,
                                    children: List.generate(5, (starIndex) {
                                      bool isFilled = starIndex < reservations[index].rating;

                                      return IconButton(
                                        onPressed: () {
                                          setState(() {
                                            reservations[index].rating = starIndex + 1;
                                          });
                                        },
                                        icon: Icon(
                                          isFilled ? Icons.star : Icons.star_border,
                                          color: Colors.black,
                                        ),
                                      );
                                    }),
                                  ),
                                  SizedBox(height: 20.0),
                                  ElevatedButton(
                                    onPressed: () {
                                      setState(() {
                                        reservations[index].status = 'Review Given';
                                      });
                                      Navigator.of(context).pop();
                                    },
                                    style: ElevatedButton.styleFrom(
                                      backgroundColor: Colors.blue.shade300,
                                    ),
                                    child: Text('Submit Review', style: TextStyle(color: Colors.black)),
                                  ),
                                ],
                              ),
                            );
                          },
                        );
                      },
                    );
                  },
                  style: ElevatedButton.styleFrom(
                    backgroundColor: Colors.blue.shade300,
                  ),
                  child: Text('Give A Review', style: TextStyle(color: Colors.black)),
                ),
              ],
              if (reservations[index].status == 'Review Given') ...[
                ListTile(
                  title: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text('Review: ${reservations[index].review}'),
                      SizedBox(height: 8),
                      Row(
                        children: [
                          _buildStarRating(reservations[index].rating),
                        ],
                      ),
                    ],
                  ),
                ),
              ],
            ],
          ),
        );
      },
    );
  }

  Widget _buildStarRating(int rating) {
    List<Widget> stars = [];
    for (int i = 0; i < 5; i++) {
      IconData iconData = i < rating ? Icons.star : Icons.star_border;
      Color color = i < rating ? Colors.black : Colors.grey;
      stars.add(Icon(iconData, color: color));
    }
    return Row(
      children: stars,
    );
  }

  Widget _buildCompanionsTab() {
    var favoritesState = context.watch<FavoritesState>();
    // Lijst van personen
    List<String> companions = [
      'Karen Damen',
      'kathleen.aerts@gmail.com',
      'd.patel@emaildomain.com',
      'Gene Thomas',
      'isla.thompson@example.org',
      'Atakan Kumas',
      'amirah.khan@emailservice.com',
      'Jutta Gilissen',
      'Mateo Rodriguez',
    ];

    return ListView.separated(
      itemCount: companions.length,
      separatorBuilder: (context, index) => Divider(),
      itemBuilder: (context, index) {
        String companion = companions[index];
        IconData leadingIcon;
        Color leadingColor;

        if (companion.contains('@')) {
          leadingIcon = Icons.help;
          leadingColor = Colors.black;
        } else {
          leadingIcon = Icons.person;
          leadingColor = Colors.black;
        }

        return ListTile(
          leading: Icon(
            leadingIcon,
            color: leadingColor,
          ),
          title: Text(
            companion,
            style: TextStyle(
              fontSize: 16.0,
              fontWeight: FontWeight.bold,
            ),
          ),
          trailing: IconButton(
            onPressed: () {
              if (favoritesState.favoriteContacts.contains(companion)) {
                favoritesState.toggleFavoriteContact(companion);
              } else {
                favoritesState.toggleFavoriteContact(companion);
              }
              favoritesState.notifyListeners();
            },
            icon: Icon(
              favoritesState.favoriteContacts.contains(companion) ? Icons.star : Icons.star_border,
              size: 30.0,
            ),
          ),
        );
      },
    );
  }

  Widget _buildTabWithIcon(String label, IconData icon) {
    return Tab(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          Icon(icon),
          SizedBox(height:2),
          Text(label),
        ],
      ),
    );
  }
}