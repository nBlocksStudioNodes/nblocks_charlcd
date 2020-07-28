# CharLCD

CharLCD node driving a standard HD44780-compatible text LCD.

Receives a string as input (such as the output from StringFormat).
When a string is received, starts from position 0,0. 
In the given string, use a "\n" to move to next line.

Example: if a StringFormat with the string "\nValue: %d" is connected,
this message will cause the LCD to jump to second line preserving the 
contents of the first line, and then print "Value: " and the value.

To clear the characters after the string, use spaces, e.g:
```
"Value: %d            "
```

If a string longer than the LCD row is sent, the extra characters are 
just ignored.

### ModifiedTextLCD

In the original TextLCD library, when the string is longer than the LCD
row, a line break is inserted and text continues in the next row. 

The ModifiedTextLCD class was then created in this node, changing this
behaviour so that the features described above can be implemented.