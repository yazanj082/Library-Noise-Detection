import './../models/device.dart';
import 'package:flutter/material.dart';

class DeviceTile extends StatelessWidget {
  final Device device;
  DeviceTile({this.device});

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.only(top: 8.0),
      child: Card(
        margin: EdgeInsets.fromLTRB(20.0, 6.0, 20.0, 0.0),
        child: ListTile(
          leading: CircleAvatar(
            radius: 25.0,
            backgroundColor: Colors.red,
          ),
          title: Text(
            '${device.num}',
          ),
          subtitle:
              Text('In  ${device.time.hour - 12} : ${device.time.minute} '),
        ),
      ),
    );
  }
}
