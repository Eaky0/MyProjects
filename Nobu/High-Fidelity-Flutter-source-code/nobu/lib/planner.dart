import 'package:flutter/material.dart';
import 'package:flutter_breadcrumb/flutter_breadcrumb.dart';
import 'package:syncfusion_flutter_datepicker/datepicker.dart';

class Plan {
  String title;
  String description;
  List<DateTime> selectedDates;
  List<TimeOfDay?> selectedTimes;

  Plan({
    required this.title,
    required this.description,
    required this.selectedDates,
    required this.selectedTimes,
  });
}

// ignore: use_key_in_widget_constructors, camel_case_types
class PlannerPage extends StatefulWidget {
  const PlannerPage({required key});

  @override
  State<PlannerPage> createState() => _PlannerPageState();
}

enum Page {what, dates, times, finalise}
class _PlannerPageState extends State<PlannerPage> {
  List<DateTime> selectedDates = [];
  List<TimeOfDay?> selectedTimes = [];
  bool confirmed = false;
  Page currentPage = Page.what;
  List<Plan> plans = [];

  void resetPage(){
    currentPage = Page.what;
  }

  void pushNestedRoute(Page page) {
    Navigator.of(context).push(MaterialPageRoute(
      builder: (BuildContext context) {
        return Scaffold(
          appBar: _buildAppBar(context),
          body: Column(
            children: [
              _buildBreadCrumbs(context),
              Expanded(
                flex: 2,
                child: _buildPage(context, page),
              ),
            ],
          ),
        );
      },
    ));
  }


  void popNestedRoute() {
    Navigator.of(context).pop();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Plan a Reservation'),
      ),
      body: Column(
        children: [
          Expanded(
            child: ListView.builder(
              itemCount: plans.length,
              itemBuilder: (context, index) {
                return GestureDetector(
                  onTap: () {
                    Navigator.push(
                      context,
                      MaterialPageRoute(builder: (context) => _buildPlan(plans[index])),
                    );
                  },
                  child: Card(
                    child: ListTile(
                      title: Text(plans[index].title),
                      subtitle: Text(plans[index].description),
                    ),
                  ),
                );
              },
            ),
          ),
          Padding(
            padding: const EdgeInsets.all(8.0),
            child: GestureDetector(
              onTap: () {
                setState(() {
                  plans.add(Plan(
                    title: 'New Plan',
                    description: 'Description of the new plan',
                    selectedDates: [],
                    selectedTimes: [],
                  ));
                });
              },
              child: Card(
                child: ListTile(
                  leading: Icon(Icons.add),
                  title: Text('Add New Plan'),
                ),
              ),
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildPlan(Plan plan) {
    if (confirmed) {
      return Scaffold(
        appBar: AppBar(
          leading: IconButton(
            icon: Icon(Icons.arrow_back),
            onPressed: () {
              Navigator.pop(context);
            },
          ),
        ),
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                'Your plan has been confirmed.',
                style: TextStyle(fontSize: 20),
              ),
              SizedBox(height: 20),
              Text(
                'Please wait for your companions to respond.',
                style: TextStyle(fontSize: 16),
              ),
            ],
          ),
        ),
      );
    } else {
      return Scaffold(
        body: Column(
          children: [
            _buildAppBar(context),
            _buildBreadCrumbs(context),
            Expanded(
              flex: 2,
              child: _buildPage(context, currentPage),
            ),
          ],
        ),
      );
    }
  }
  PreferredSizeWidget  _buildAppBar(BuildContext context) {
    return AppBar(
      toolbarHeight: 120.0,
      title: const Text(
        'Plan a Reservation',
        style: TextStyle(
          fontFamily: 'Pilgrim',
          fontSize: 35.0,
        ),
      ),
      centerTitle: true,
    );
  }

  Widget _buildBreadCrumbs(BuildContext context){
    final List<BreadCrumbItem> items = [
      BreadCrumbItem(
        content: Text('What'),
      ),
      BreadCrumbItem(
      content: Text('Dates'),
      ),
      BreadCrumbItem(
      content: Text('Times'),
      ),
      BreadCrumbItem(
      content: Text('Finalise'),
      )
    ];
    final Widget divider = Icon(Icons.chevron_right);

    return Padding(
      padding: const EdgeInsets.only(left:20.0, right: 20.0, bottom: 40.0),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: List.generate(items.length * 2 - 1, (index) {
            if (index.isEven) {
              return items[index ~/ 2].content;
            } else {
              return divider;
            }
          }),
      ),
    );
  }

  Widget _buildPage(BuildContext context, Page page) {
    switch (page) {
      case Page.what:
        return _buildPageWhat(context);
      case Page.dates:
        return _buildPageDates(context);
      case Page.times:
        return _buildPageTimes(context, selectedDates);
      case Page.finalise:
        return _buildPageFinalise(context);
    }
  }

  Widget _buildPageWhat(BuildContext context) {
    return SingleChildScrollView(
      child: Padding(
        padding: const EdgeInsets.only(left: 20.0, right: 20.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(
              'Title',
              style: TextStyle(
                fontSize: 20.0,
              ),
            ),
            Text(
              'Give your event a name your guests will recognise',
              style: TextStyle(
                fontSize: 15.0,
                color: Colors.grey,
              ),
            ),
            TextField(),
            SizedBox(height: 100,),
            Text(
              'Description (optional)',
              style: TextStyle(
                fontSize: 20.0,
              ),
            ),
            Text(
              'Describe your event in further detail',
              style: TextStyle(
                fontSize: 15.0,
                color: Colors.grey,
              ),
            ),
            TextField(
              minLines: 4,
              maxLines: 4,
            ),
            SizedBox(height: 80,),

            Padding(
              padding: const EdgeInsets.only(left: 50.0, right: 50.0),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  ElevatedButton(
                    onPressed: () => pushNestedRoute(Page.dates),
                    style: ElevatedButton.styleFrom(
                      padding: EdgeInsets.symmetric(horizontal: 20, vertical: 10),
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(8.0),
                      ),
                      backgroundColor: Colors.blue.shade200,
                    ),
                    child: Row(
                      mainAxisSize: MainAxisSize.min,
                      children: [
                        Text(
                          'Next',
                          style: TextStyle(
                            fontSize: 20,
                            color: Colors.black,
                          ),
                        ),
                        SizedBox(width: 10),
                        Icon(Icons.chevron_right),
                      ],
                    ),
                  ),
                ],
              ),
            )
          ],
        ),
      ),
    );
  }

  Widget _buildPageDates(BuildContext context){
    return Padding(
      padding: const EdgeInsets.only(left: 20.0, right: 20.0),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(
            'Pick your available dates',
            style: TextStyle(
              fontSize: 20.0,
            ),
          ),
          Text(
            'Pick dates that work for you',
            style: TextStyle(
              fontSize: 15.0,
              color: Colors.grey,
            ),
          ),
          SizedBox(height: 20,),
          Expanded(
            child: SfDateRangePicker(
              selectionMode: DateRangePickerSelectionMode.multiple,
              onSelectionChanged: (DateRangePickerSelectionChangedArgs args) {
                setState(() {
                  selectedDates = args.value.cast<DateTime>();
                });
              },
              backgroundColor: Colors.blue.shade50,
              headerStyle: DateRangePickerHeaderStyle(
                backgroundColor: Colors.blue.shade50,
                textStyle: TextStyle(
                  fontSize: 18,
                ),
              ),
            ),
          ),
          SizedBox(height: 20,),
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 20.0),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                ElevatedButton(
                  onPressed: popNestedRoute,
                  style: ElevatedButton.styleFrom(
                    padding: EdgeInsets.symmetric(horizontal: 20, vertical: 10),
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(8.0),
                    ),
                    backgroundColor: Colors.blue.shade200,
                  ),
                  child: Row(
                    children: [
                      Icon(Icons.chevron_left),
                      SizedBox(width: 10),
                      Text(
                        'Previous',
                        style: TextStyle(
                          fontSize: 20,
                          color: Colors.black,
                        ),
                      ),
                    ],
                  ),
                ),
                ElevatedButton(
                  onPressed: () => pushNestedRoute(Page.times),
                  style: ElevatedButton.styleFrom(
                    padding: EdgeInsets.symmetric(horizontal: 20, vertical: 10),
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(8.0),
                    ),
                    backgroundColor: Colors.blue.shade200,
                  ),
                  child: Row(
                    children: [
                      Text(
                        'Next',
                        style: TextStyle(
                          fontSize: 20,
                            color: Colors.black,
                        ),
                      ),
                      SizedBox(width: 10),
                      Icon(Icons.chevron_right),
                    ],
                  ),
                ),
              ],
            ),
          )
        ],
      ),
    );
  }

  Widget _buildPageTimes(BuildContext context, List<DateTime> selectedDates){
    return Padding(
      padding: const EdgeInsets.all(20.0),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(
            'Pick your available times',
            style: TextStyle(
              fontSize: 20.0,
            ),
          ),
          Text(
            'Pick times that work for you',
            style: TextStyle(
              fontSize: 15.0,
              color: Colors.grey,
            ),
          ),
          SizedBox(height: 20),
          Expanded(
            child: ListView.builder(
              itemCount: selectedDates.length,
              itemBuilder: (context, index) {
                DateTime currentDate = selectedDates[index];
                TimeOfDay? currentTime = selectedTimes.length > index ? selectedTimes[index] : null;
                String timeStr = currentTime != null ? '${currentTime.hour}:${currentTime.minute}' : '00:00';

                return Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      '${currentDate.day}/${currentDate.month}/${currentDate.year}',
                      style: TextStyle(
                        fontSize: 18,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                    SizedBox(height: 10),
                    Padding(
                      padding: const EdgeInsets.only(left: 10.0),
                      child: Container(
                        padding: EdgeInsets.all(8.0),
                        decoration: BoxDecoration(
                          border: Border.all(color: Colors.black),
                          borderRadius: BorderRadius.circular(8.0),
                        ),
                        child: Text(
                          timeStr,
                          style: TextStyle(
                            fontSize: 18,
                          ),
                        ),
                      ),
                    ),
                    SizedBox(height: 10),
                    ElevatedButton(
                      onPressed: () async {
                        TimeOfDay? picked = await _selectTime(context, currentTime, index);
                        if (picked != null) {
                          setState(() {
                            if (selectedTimes.length > index) {
                              selectedTimes[index] = picked;
                            } else {
                              selectedTimes.add(picked);
                            }
                          });
                        }
                      },
                      child: Text('Select Time'),
                    ),
                    SizedBox(height: 20),
                  ],
                );
              },
            ),
          ),
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 20.0),
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                ElevatedButton(
                  onPressed: popNestedRoute,
                  style: ElevatedButton.styleFrom(
                    padding: EdgeInsets.symmetric(horizontal: 20, vertical: 10),
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(8.0),
                    ),
                    backgroundColor: Colors.blue.shade200,
                  ),
                  child: Row(
                    children: [
                      Icon(Icons.chevron_left),
                      SizedBox(width: 10),
                      Text(
                        'Previous',
                        style: TextStyle(
                          fontSize: 20,
                          color: Colors.black,
                        ),
                      ),
                    ],
                  ),
                ),
                ElevatedButton(
                  onPressed: () => pushNestedRoute(Page.finalise),
                  style: ElevatedButton.styleFrom(
                    padding: EdgeInsets.symmetric(horizontal: 20, vertical: 10),
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(8.0),
                    ),
                    backgroundColor: Colors.blue.shade200,
                  ),
                  child: Row(
                    children: [
                      Text(
                        'Next',
                        style: TextStyle(
                          fontSize: 20,
                          color: Colors.black,
                        ),
                      ),
                      SizedBox(width: 10),
                      Icon(Icons.chevron_right),
                    ],
                  ),
                ),
              ],
            ),
          )
        ],
      ),
    );
  }


  Future<TimeOfDay?> _selectTime(BuildContext context, TimeOfDay? initialTime, int index) async {
    TimeOfDay? picked = await showTimePicker(
      context: context,
      initialTime: initialTime ?? TimeOfDay(hour: 0, minute: 0),
    );

    if (picked != null) {
      setState(() {
        if (selectedTimes.length > index) {
          selectedTimes[index] = picked;
        } else {
          selectedTimes.add(picked);
        }
      });

      WidgetsBinding.instance!.addPostFrameCallback((_) {
        popNestedRoute();
        pushNestedRoute(Page.times);
      });
    }

    return picked;
  }


  Widget _buildPageFinalise(BuildContext context) {
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

      List<bool> checkedList = List<bool>.generate(companions.length, (index) => false);

      return Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(
              'Select Companions:',
              style: TextStyle(fontSize: 20),
            ),
            SizedBox(height: 20),
            Expanded(
              child: ListView.builder(
                shrinkWrap: true,
                itemCount: companions.length,
                itemBuilder: (_, int index) {
                  final companion = companions[index];
                  final leadingIcon = getLeadingIcon(companion);
                  final leadingColor = getLeadingColor(companion);

                  return StatefulBuilder(
                    builder: (BuildContext context, StateSetter setState) {
                      return CheckboxListTile(
                        title: Text(
                          companion,
                          style: const TextStyle(fontSize: 18.0),
                        ),
                        secondary: Icon(
                          leadingIcon,
                          color: leadingColor,
                        ),
                        controlAffinity: ListTileControlAffinity.trailing,
                        value: checkedList[index],
                        onChanged: (bool? value) {
                          setState(() {
                            checkedList[index] = value!;
                          });
                        },
                      );
                    },
                  );

                },
              ),
            ),
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 20.0),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  ElevatedButton(
                    onPressed: popNestedRoute,
                    style: ElevatedButton.styleFrom(
                      padding: EdgeInsets.symmetric(horizontal: 20, vertical: 10),
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(8.0),
                      ),
                      backgroundColor: Colors.blue.shade200,
                    ),
                    child: Row(
                      children: [
                        Icon(Icons.chevron_left),
                        SizedBox(width: 10),
                        Text(
                          'Previous',
                          style: TextStyle(
                            fontSize: 20,
                            color: Colors.black,
                          ),
                        ),
                      ],
                    ),
                  ),
                  ElevatedButton(
                    onPressed: () {
                      setState(() {
                        confirmed = true;
                      });
                      Navigator.of(context).popUntil((route) => route.isFirst);
                    },
                    style: ElevatedButton.styleFrom(
                      padding: EdgeInsets.symmetric(horizontal: 20, vertical: 10),
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(8.0),
                      ),
                      backgroundColor: Colors.blue.shade200,
                    ),
                    child: Row(
                      children: [
                        Text(
                          'Finalise plan',
                          style: TextStyle(
                            fontSize: 20,
                            color: Colors.black,
                          ),
                        ),
                        SizedBox(width: 10),
                        Icon(Icons.chevron_right),
                      ],
                    ),
                  ),
                ],
              ),
            )
          ],
        ),
      );
    }
  IconData getLeadingIcon(String companion) {
    return companion.contains('@') ? Icons.help : Icons.person;
  }

  Color getLeadingColor(String companion) {
    return Colors.black;
  }
}

