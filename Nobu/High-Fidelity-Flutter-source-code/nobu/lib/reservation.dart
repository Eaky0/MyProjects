import 'dart:async';

import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:faker/faker.dart';

class Pair<E, F> {
  E first;
  F last;

  Pair(this.first, this.last);
}

class Companion{
  String? firstName;
  String? lastName;
  String? email;
  bool isFavourite;

  Companion(this.firstName, this.lastName, this.email, [this.isFavourite = false]);
  Companion.account(this.firstName, this.lastName, [this.isFavourite = false]){
    email = null;
  }
  Companion.emailOnly(this.email, [this.isFavourite = false]){
    firstName = null;
    lastName = null;
  }

  @override
  String toString() {
    return '$firstName $lastName: $email ($isFavourite)';
  }

  String get name{
    if(firstName != null && lastName != null){
      return '$firstName $lastName';
    }
    else if (email != null){
      return '$email';
    }
    else{
      return '';
    }
  }

  bool isAccount(){
    return firstName != null && lastName != null;
  }
}

class ReservationData{
  final String restaurantName;
  final List<Companion> companions;
  final DateTime datetime;
  final bool limo;

  ReservationData(this.restaurantName, this.companions, this.datetime, this.limo);
}

class Reservation extends StatefulWidget{
  final String restaurantName;

  const Reservation({Key? key, required this.restaurantName}) : super(key: key);

  @override
  State<Reservation> createState() => _ReservationState();
}

class _ReservationState extends State<Reservation> {

  static List<Companion> companionsList = [
    Companion.account("Karen", "Damen", true),
    Companion.emailOnly("kathleen.aerts@gmail.com", true),
    Companion.emailOnly("d.patel@emaildomain.com"),
    Companion.account("Mateo", "Rodriguez"),
    Companion.emailOnly("isla.thompson@example.org"),
    Companion.emailOnly("amirah.khan@emailservice.com"),
    Companion.account("Atakan", "Kumas"),
    Companion.account("Jutta", "Gilissen"),
    // Companion.account("Karen", "Damen", true),
    // Companion.emailOnly("kathleen.aerts@gmail.com", true),
    // Companion.emailOnly("d.patel@emaildomain.com"),
    // Companion.account("Mateo", "Rodriguez"),
    // Companion.emailOnly("isla.thompson@example.org"),
    // Companion.emailOnly("amirah.khan@emailservice.com"),
    // Companion.account("Atakan", "Kumas"),
    // Companion.account("Jutta", "Gilissen"),
    // Companion.account("Karen", "Damen", true),
    // Companion.emailOnly("kathleen.aerts@gmail.com", true),
    // Companion.emailOnly("d.patel@emaildomain.com"),
    // Companion.account("Mateo", "Rodriguez"),
    // Companion.emailOnly("isla.thompson@example.org"),
    // Companion.emailOnly("amirah.khan@emailservice.com"),
    // Companion.account("Atakan", "Kumas"),
    // Companion.account("Jutta", "Gilissen"),
  ];


  List<Companion> companionsChosen = [];
  DateTime? datetime;
  bool limoService = false;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Column(
        children: [
          Expanded(
            child: SingleChildScrollView(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.start,
                children: <Widget>[
                  _buildAppBar(context),
                  _buildNameBar(widget.restaurantName),
                  _buildInputFields(context, companionsList, companionsChosen),
                ],
              ),
            ),
          ),
          TextButton(
            style: TextButton.styleFrom(
              backgroundColor: Colors.blue.shade200,
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(8),
              ),
            ),
            onPressed: confirmReservation,
            child: const Padding(
              padding: EdgeInsets.all(4.0),
              child: Text(
                'Confirm',
                style: TextStyle(
                  fontSize: 20.0,
                  color: Colors.black,
                ),
              ),
            ),
          ),
          SizedBox(height: 20.0),
        ],
      ),
    );
  }

  void confirmReservation() {
    Fluttertoast.showToast(
        msg: "Your reservation has been made.",
        toastLength: Toast.LENGTH_SHORT,
        gravity: ToastGravity.TOP,
        timeInSecForIosWeb: 2,
        backgroundColor: Colors.blue.shade100,
        textColor: Colors.black,
        fontSize: 20.0
    );
    Navigator.pop(context);
  }

  Widget _buildAppBar(BuildContext context) {
    return AppBar(
      toolbarHeight: 120.0,
      leading: IconButton(
        icon: const Icon(Icons.navigate_before),
        onPressed: () {
          Navigator.pop(context);
        },
        iconSize: 50.0,
      ),
      title: const Text(
        'Make Reservation',
        style: TextStyle(
          fontFamily: 'Pilgrim',
          fontSize: 35.0,
        ),
      ),
      centerTitle: true,
    );
  }

  Widget _buildNameBar(String restaurant) {
    return Container(
      color: Colors.grey,
      padding: const EdgeInsets.all(2.0),
      alignment: Alignment.center,
      child: Text(
        restaurant.toUpperCase(),
        style: const TextStyle(
          fontSize: 40.0,
          color: Colors.white,
        ),
      ),
    );
  }

  Widget _buildInputFields(BuildContext context, List<Companion> companions,
      List<Companion> companionsChosen) {
    double textSize = 30.0;
    return Padding(
      padding: const EdgeInsets.all(50.0),
      child: Column(
        children: [
          _buildFieldCompanions(
              context, textSize, companions, companionsChosen),
          Padding(
            padding: const EdgeInsets.only(top: 20.0),
            child: _buildFieldDate(context, textSize),
          ),
          Padding(
            padding: const EdgeInsets.only(top: 20.0),
            child: _buildFieldTime(context, textSize),
          ),
          Padding(
            padding: const EdgeInsets.only(top: 20.0),
            child: _buildFieldLimo(context, textSize),
          ),
        ],
      ),
    );
  }


  Widget _buildFieldCompanions(BuildContext context, double textSize,
      List<Companion> companions, List<Companion> companionsChosen) {
    return Container(
      decoration: BoxDecoration(
          borderRadius: const BorderRadius.all(Radius.circular(10)),
          shape: BoxShape.rectangle,
          border: Border.all(
            color: Colors.black,
            width: 1,
          )
      ),
      child: GestureDetector(
        onTap: () {},
        child: Row(
          children: [
            const Padding(
              padding: EdgeInsets.all(20.0),
              child: Icon(
                Icons.groups,
                size: 50,),
            ),
            Padding(
              padding: const EdgeInsets.only(left: 10.0),
              child: Text(
                  (companionsChosen.length + 1).toString(),
                  // empty -> count host
                  style: TextStyle(
                    fontSize: textSize,
                  )
              ),
            ),
            Expanded(
                child: Container()
            ),
            Padding(
              padding: const EdgeInsets.only(right: 50.0),
              child: TextButton(
                style: TextButton.styleFrom(
                    backgroundColor: Colors.blue.shade200,
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(8),
                    )
                ),
                onPressed: () async {
                  companionsChosen = (await _showCompanionDialog(context))!;
                },
                child: const Text(
                  'Add user',
                  style: TextStyle(
                    color: Colors.black,
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Future<List<Companion>?> _showCompanionDialog(BuildContext context) async {
    return showDialog<List<Companion>>(
      context: context,
      barrierDismissible: false,
      builder: (BuildContext context) {
        return CompanionDialog(
            onConfirm: (List<Companion> companions) {
              return companions;
            });
      },
    );
  }

  void submitCompanions(BuildContext context) {
    Navigator.pop(context, _CompanionCheckBoxListState()
        .getCheckedCompanions());
  }

  String getDateFormatted(DateTime? date) {
    String seperator = '-';
    return date!.day.toString() + seperator + date.month.toString() +
        seperator + date.year.toString();
  }

  Widget _buildFieldDate(BuildContext context, double textSize) {
    String dateStr;
    datetime == null ? dateStr = 'Date' : dateStr = getDateFormatted(datetime);
    return GestureDetector(
      onTap: () {
        _selectDate(context);
      },
      child: Container(
        decoration: BoxDecoration(
          borderRadius: const BorderRadius.all(Radius.circular(10)),
          shape: BoxShape.rectangle,
          border: Border.all(
            color: Colors.black,
            width: 1,
          ),
        ),
        child: Row(
          children: [
            const Padding(
              padding: EdgeInsets.all(20.0),
              child: Icon(
                Icons.calendar_today,
                size: 50,
              ),
            ),
            Padding(
              padding: const EdgeInsets.only(left: 10.0),
              child: Text(
                dateStr,
                style: TextStyle(
                  fontSize: textSize,
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Future<void> _selectDate(BuildContext context) async {
    final DateTime? picked = await showDatePicker(
      context: context,
      initialDate: datetime ?? DateTime.now(),
      firstDate: DateTime.now(),
      lastDate: DateTime(2100),
    );
    if (picked != null) {
      setState(() {
        if (datetime != null) {
          datetime = DateTime(
              picked.year, picked.month, picked.day, datetime!.hour,
              datetime!.minute);
        } else {
          datetime = picked;
        }
      });
    }
  }

  String getTimeFormatted(DateTime? date) {
    String seperator = ':';
    return date!.hour.toString() + seperator + date.minute.toString();
  }

  Widget _buildFieldTime(BuildContext context, double textSize) {
    String timeStr;
    datetime == null ? timeStr = 'Time' : timeStr = getTimeFormatted(datetime);
    return GestureDetector(
      onTap: () {
        _selectTime(context);
      },
      child: Container(
        decoration: BoxDecoration(
          borderRadius: const BorderRadius.all(Radius.circular(10)),
          shape: BoxShape.rectangle,
          border: Border.all(
            color: Colors.black,
            width: 1,
          ),
        ),
        child: Row(
          children: [
            const Padding(
              padding: EdgeInsets.all(20.0),
              child: Icon(
                Icons.access_time_rounded,
                size: 50,
              ),
            ),
            Padding(
              padding: const EdgeInsets.only(left: 10.0),
              child: Text(
                timeStr,
                style: TextStyle(
                  fontSize: textSize,
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Future<void> _selectTime(BuildContext context) async {
    final TimeOfDay? picked = await showTimePicker(
      context: context,
      initialTime: TimeOfDay.fromDateTime(datetime ?? DateTime.now()),
    );
    if (picked != null &&
        picked != TimeOfDay.fromDateTime(datetime ?? DateTime.now())) {
      setState(() {
        datetime = DateTime(
            datetime!.year, datetime!.month, datetime!.day, picked.hour,
            picked.minute);
      });
    }
  }

  Widget _buildFieldLimo(BuildContext context, double textSize) {
    return Column(
      children: [
        Container(
          decoration: BoxDecoration(
            borderRadius: const BorderRadius.all(Radius.circular(10)),
            shape: BoxShape.rectangle,
            border: Border.all(
              color: Colors.black,
              width: 1,
            ),
          ),
          child: Row(
            children: [
              const Padding(
                padding: EdgeInsets.all(20.0),
                child: Icon(
                  Icons.directions_car_rounded,
                  size: 50,
                ),
              ),
              Padding(
                padding: const EdgeInsets.only(left: 5.0),
                child: Checkbox(
                  value: limoService,
                  onChanged: (bool? val) {
                    setState(() {
                      limoService = val ?? false;
                    });
                  },
                ),
              ),
              Flexible(
                child: const Text(
                  'Yes, I want the Limousine Service',
                  style: TextStyle(
                    fontSize: 15,
                  ),
                ),
              ),
            ],
          ),
        ),
        if (limoService)
          Padding(
            padding: const EdgeInsets.fromLTRB(10, 0, 10, 10),

            child: SizedBox(
              height: 40.0,
              width: 160,
              child: ElevatedButton.icon(
                onPressed: () {
                  showDialog(
                      context: context,
                      builder: (context) {return _buildLocationDialog(context);}
                  );
                },
                label: const Text("Location", style: TextStyle(fontSize: 20)),
                icon: Icon(Icons.fmd_good_outlined, size: 22,),
                style: ElevatedButton.styleFrom(
                  elevation: 0,
                  foregroundColor: Colors.black,
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(10),
                    side: BorderSide(
                      color: Colors.black,
                      width: 1,
                    ),

                  ),
                ),
              ),
            ),
          ),
      ],
    );
  }

  Widget _buildLocationDialog(BuildContext context) {
    return AlertDialog(
      actions: [
        TextButton(
            onPressed: () {
              Navigator.of(context).pop();
            },
            child: const Text("Cancel"))
      ],
      title: const Text("Location"),
      contentPadding: EdgeInsets.all(10.0),
      content: Stack(
        children: [
          Positioned(
            child: Padding(
              padding: const EdgeInsets.fromLTRB(0, 60, 0, 0),
              child: SingleChildScrollView(
                child: Column(
                  children: List.generate(
                    30,
                        (index) =>
                        GestureDetector(
                          onTap: () {
                            Navigator.of(context).pop();
                          },
                          child: Padding(
                            padding: const EdgeInsets.all(8.0),
                            child: Container(
                              decoration: BoxDecoration(
                                color: Colors.blue.shade100,
                                border: Border.all(color: Colors.black),
                                borderRadius: BorderRadius.circular(15),
                              ),
                              child: SizedBox(
                                width: 300,
                                height: 50,
                                child: Row(
                                  mainAxisAlignment: MainAxisAlignment.center,

                                  children: [
                                    Flexible(
                                      child: Text(
                                          "${faker.address.city()}, ${faker
                                              .address.country()}",
                                          overflow: TextOverflow.ellipsis
                                      ),
                                    )
                                  ],
                                ),
                              ),
                            ),
                          ),
                        ),
                  ),
                ),
              ),
            ),
          ),
          Positioned(
            top: 0,
            left: 0,
            right: 0,
            child: SearchBar(),
          ),
        ],
      ),
    );
  }
}

//#region companions helpers
final keyCheckBoxListState = new GlobalKey<_CompanionCheckBoxListState>();
class CompanionCheckBoxList extends StatefulWidget{
  const CompanionCheckBoxList({super.key});

  @override
  _CompanionCheckBoxListState createState() => _CompanionCheckBoxListState();
}

class _CompanionCheckBoxListState extends State<CompanionCheckBoxList> {
  late List<Companion> companionsList;
  late List<bool> checked;
  late int nFavourites;

  _CompanionCheckBoxListState() {
    List<Companion> companionsListFavourites = [];
    List<Companion> companionsListOther = [];

    for (var companion in _ReservationState.companionsList) {
      if (companion.isFavourite) {
        companionsListFavourites.add(companion);
      }
      else {
        companionsListOther.add(companion);
      }
    }
    nFavourites = companionsListFavourites.length;
    companionsList = companionsListFavourites + companionsListOther;
    checked = companionsList.map((c) => false).toList();
  }

  List<Companion> getCheckedCompanions(){
    List<Companion> companionsChecked = [];
    for (int i= 0; i < checked.length; i++){
      if (checked[i]){
        companionsChecked.add(companionsList[i]);
      }
    }
    return companionsChecked;
  }

  @override
  Widget build(BuildContext context) {
    bool dividerSet = false;
    return Column(
      children: [
        Container(
          color: Colors.grey,
          padding: const EdgeInsets.all(10.0),
          child: const Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Text('Favourites',
                style: TextStyle(
                  fontSize: 20.0,
                ),
              ),
              Icon(Icons.star),
            ],
          ),
        ),
        ListView.builder(
            shrinkWrap: true,
            itemCount: companionsList.length,
            itemBuilder: (_, int index) {
              if (!dividerSet && index == nFavourites) {
                dividerSet = true;
                return const Divider(
                );
              }
              return CheckboxListTile(
                title: Text(
                  companionsList[index].name,
                  style: const TextStyle(
                    fontSize: 20.0,
                  ),
                ),
                secondary: companionsList[index].isAccount()
                    ? const Icon(Icons.person)
                    : const Icon(Icons.question_mark_rounded),
                controlAffinity: ListTileControlAffinity.trailing,
                value: checked[index],
                onChanged: (bool? value) {
                  setState(() {
                    print('checkbox ' + (companionsList[index].name).toString() + ' clicked');
                    checked[index] = value!;
                  });
                },
              );
            }
        ),
      ],
    );
  }
}

class CompanionDialog extends StatefulWidget{
  @override
  State<StatefulWidget> createState() => _CompanionDialogState();

  final Function(List<Companion> companions) onConfirm;

  const CompanionDialog({super.key, required this.onConfirm});
}

class _CompanionDialogState extends State<CompanionDialog> {
  late TextEditingController controller;

  @override
  void initState() {
    super.initState();

    controller = TextEditingController();
  }

  @override
  void dispose() {
    controller.dispose();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: const Text('Add Companions'),
      content: SizedBox(
        width: double.maxFinite,
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Padding(
              padding: const EdgeInsets.only(bottom: 20.0),
              child: TextField(
                controller: controller,
                // autofocus: true,
                decoration: const InputDecoration(hintText: 'Search companion'),
                autofocus: true,
              ),
            ),
            Expanded(
              child: SingleChildScrollView(
                child: CompanionCheckBoxList(key: keyCheckBoxListState),
              ),
            ),
          ],
        ),
      ),
      actions: [
        TextButton(
            child: const Text('Confirm'),
            onPressed: () {
              widget.onConfirm(
                  keyCheckBoxListState.currentState!.getCheckedCompanions());
              Navigator.pop(context);
            }
        ),
      ],
    );
  }
}

//endregion