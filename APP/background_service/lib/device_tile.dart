import './models/device.dart';
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
            backgroundImage: AssetImage('assets/noise.png'),
          ),
          title: Text(
            '${device.num}',
          ),
          subtitle: device.time.hour > 12
              ? Text('${device.time.hour - 12} : ${device.time.minute} ')
              : Text('${device.time.hour} : ${device.time.minute} '),
        ),
      ),
    );
  }
}
