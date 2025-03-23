import 'package:flutter/material.dart';

class Booking {
  final String restaurantName;
  final DateTime date;
  final TimeOfDay time;
  final int partySize;
  final bool hasLimousine;
  final List<String> contacts;
  String review;
  String status;
  int rating = 0;

  Booking({
    required this.restaurantName,
    required this.date,
    required this.time,
    required this.partySize,
    required this.hasLimousine,
    required this.contacts,
    required this.review,
    required this.status,
    required this.rating,
  });
}

class bookingCard extends StatefulWidget {
  final Booking booking;

  const bookingCard({Key? key, required this.booking}) : super(key: key);

  @override
  _BookingCardState createState() => _BookingCardState();
}

class _BookingCardState extends State<bookingCard> {
  bool _isExpanded = false;

  @override
  Widget build(BuildContext context) {
    return Card(
      margin: EdgeInsets.all(8.0),
      child: ExpansionTile(
          title: Text(widget.booking.restaurantName),
          subtitle: Text(
              '${widget.booking.date.toString().split(' ')[0]} | ${widget
                  .booking.time.format(context)}'),
          children: [
            ListTile(
              title: Text(
                  'Date: ${widget.booking.date.toString().split(' ')[0]}'),
            ),
            ListTile(
              title: Text('Time: ${widget.booking.time.format(context)}'),
            ),
            ListTile(
              title: Text('Party Size: ${widget.booking.partySize}'),
            ),
            ListTile(
              title: Text(
                  'Limousine: ${widget.booking.hasLimousine ? 'Yes' : 'No'}'),
            ),
            ListTile(
              title: Text('Contacts: ${widget.booking.contacts.join(', ')}'),
            ),
            ListTile(
              title: Text('Review: ${widget.booking.review}'),
            ),
          ]
      ),
    );
  }
}
