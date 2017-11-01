# -*- coding: utf-8 -*-
from irc3.plugins.command import command
import irc3
import re

@irc3.plugin
class Plugin:
    def __init__(self, bot):
        self.bot = bot
        self.pieces = []
        self.valid_cmds = ["up", "down", "left", "right"]
    @irc3.event(irc3.rfc.JOIN)
    def say_hi(self, mask, channel, **kw):
        #Say hi when someone join a channel
        if mask.nick != self.bot.nick:
            self.bot.privmsg(channel, 'Hi %s!' % mask.nick)
        else:
            self.bot.privmsg(channel, 'Hi!')

    @irc3.event(irc3.rfc.PRIVMSG)
    def process(self, mask=None, event=None, target=None, data=None):
      def insert_x(command):
       for i, c in enumerate(command):
        if c.isdigit():
            break
       return command[:i] + 'x' + command[i:]
       #check for valid commands, !(up|down|left|right)(1-49) e.g. !down35
      if data.startswith(("!up", "!down", "!left", "!right")) and len(data) < 9 and re.search('^(!right|!left|!up|!down)([1-9]|[1-4][0-9]|50|40|30|20|10)$',data):
       data = insert_x(data)
       for i in self.valid_cmds:
         if i in data:
          self.pieces.append(data)
          if len(self.pieces) > 4:
           output = str(self.pieces)
           cleanString = re.sub('\W+',' ', output )
           for t in (('left', '1'), ('right','2'), ('up','3'), ('down', '4')):
            cleanString = cleanString.replace(*t)
           cleanString = cleanString[1:]
           output = output.replace('x', ' ')
           output = re.sub('\W+',' ', output )
           self.bot.privmsg(target, "Now executing commands:{0}".format(output)) # Print executed commands to IRC
           print(cleanString) # Print Arduino-formatted command list to stdout, redirect this to the Arduino device.
           self.pieces = []
