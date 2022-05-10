Weight Graphing Utility
-----------------------

This is a simple utility that graphs body weight over time, computing a 10-day
moving average and showing how daily weight influences this moving average.

This utility is written in C. It parses an XML file using expat.  The XML file
looks like this:

```xml
<weight-log>
    <beginning-averages moving-average="130.5"/>
    <log date="05/01" weight="127.2"/>
    <log date="05/02" weight="126.8"/>
    <log date="05/03" weight="127.0"/>
</weight-log>
```

Build dependencies
==================

This library depends on expat and RCPR. Both should be installed and in the
`PKG_CONFIG_PATH`.

Building
========

This utility is built using cmake.
