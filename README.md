## Introduction

Jack (**J**SON **ack**) is a JSON search utility, aiming for speed.

## Example Usage

Given an example newline-delimited JSON file:

	$ cat events.json
    {"id":1,"created_at":"Sat Jan 07 03:18:00 +0000 2012"}
    {"id":2,"created_at":"Sat Jan 07 03:20:00 +0000 2012"}
    {"id":3,"created_at":"Sat Jan 07 03:22:00 +0000 2012"}

Search by key (note the ending colon):

    $ jack created_at: events.json
    Sat Jan 07 03:18:00 +0000 2012
    Sat Jan 07 03:20:00 +0000 2012
    Sat Jan 07 03:22:00 +0000 2012

## Thanks

* [ack](http://betterthangrep.com/) - for three-quarters of the name
  and being awesome
* ["why GNU grep is fast"](http://lists.freebsd.org/pipermail/freebsd-current/2010-August/019310.html) - for continued inspiration
* [GitHub Watchers Like You](https://github.com/jcsalterego/jack/watchers)

## License

Jack is BSD-licensed. See `LICENSE` for details.
