/*
 * Copyright 2007 Doxological Ltd.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __FAXPP__EVENT_H
#define __FAXPP__EVENT_H

#include "text.h"

/// An enumeration of the event types returned by the parser
typedef enum {
  NO_EVENT,
  START_DOCUMENT_EVENT,
  END_DOCUMENT_EVENT,
  DOCTYPE_EVENT,
  START_ELEMENT_EVENT,
  SELF_CLOSING_ELEMENT_EVENT,
  END_ELEMENT_EVENT,
  CHARACTERS_EVENT,
  CDATA_EVENT,
  IGNORABLE_WHITESPACE_EVENT,
  COMMENT_EVENT,
  PI_EVENT,
  ENTITY_REFERENCE_EVENT,       ///< Reference to an external parsed entity that has not been parsed yet, or a built in entity
  DEC_CHAR_REFERENCE_EVENT,
  HEX_CHAR_REFERENCE_EVENT,
  ENTITY_REFERENCE_START_EVENT, ///< Delimits the start of an expanded entity reference
  ENTITY_REFERENCE_END_EVENT,   ///< Delimits the end of an expanded entity reference
  START_EXTERNAL_ENTITY_EVENT,  ///< Occurs when an external entity parsed by the user starts
  END_EXTERNAL_ENTITY_EVENT     ///< Occurs when an external entity parsed by the user ends
} FAXPP_EventType;

/// An item in a linked list of a FAXPP_Attribute object's value
typedef struct FAXPP_AttrValue_s {
  /// The type of the attribute value. \details Can be CHARACTERS_EVENT, ENTITY_REFERENCE_EVENT, DEC_CHAR_REFERENCE_EVENT, HEX_CHAR_REFERENCE_EVENT,
  /// ENTITY_REFERENCE_START_EVENT and ENTITY_REFERENCE_END_EVENT
  FAXPP_EventType type;
  /// The name of the item in the attribute's value. \details Present for event types ENTITY_REFERENCE_EVENT, DEC_CHAR_REFERENCE_EVENT,
  /// HEX_CHAR_REFERENCE_EVENT and ENTITY_REFERENCE_START_EVENT
  FAXPP_Text name;
  /// The value of the item in the attribute's value. \details Present for all possible event types except ENTITY_REFERENCE_START_EVENT and
  /// ENTITY_REFERENCE_END_EVENT
  FAXPP_Text value;

  unsigned int line;   ///< The line the attribute value started on
  unsigned int column; ///< The column the attribute value started on

  struct FAXPP_AttrValue_s *next; ///< The next item in the attribute's value, or 0

  /// Private - \b Do \b not \b use
  struct FAXPP_AttrValue_s *dealloc_next;
} FAXPP_AttrValue;

/// An attribute, part of the FAXPP_Event object
typedef struct {
  FAXPP_Text prefix;     ///< The prefix of the attribute
  FAXPP_Text uri;        ///< The URI of the attribute
  FAXPP_Text name;       ///< The name of the attribute

  FAXPP_AttrValue value; ///< A linked list of the attribute value

  unsigned int xmlns_attr:1; ///< Set to 1 if the attribute is a namespace declaration
  unsigned int xml_attr:1;   ///< Set to 1 if the attribute has a prefix of "xml"

  unsigned int line;   ///< The line the attribute started on
  unsigned int column; ///< The column the attribute started on
} FAXPP_Attribute;

/// A structure containing event information, returned by the parser
typedef struct {
  FAXPP_EventType type;    ///< The type of the event

  FAXPP_Text prefix;       ///< The prefix of the event. \details Present for event types DOCTYPE_EVENT, START_ELEMENT_EVENT, SELF_CLOSING_ELEMENT_EVENT, and END_ELEMENT_EVENT
  FAXPP_Text uri;          ///< The URI of the event. \details Present for event types START_ELEMENT_EVENT, SELF_CLOSING_ELEMENT_EVENT, and END_ELEMENT_EVENT
  /// The name of the event. \details Present for event types DOCTYPE_EVENT, START_ELEMENT_EVENT, SELF_CLOSING_ELEMENT_EVENT, END_ELEMENT_EVENT, PI_EVENT,
  /// ENTITY_REFERENCE_EVENT, DEC_CHAR_REFERENCE_EVENT, and HEX_CHAR_REFERENCE_EVENT
  FAXPP_Text name;

  /// The value of the event. \details Present for event types CHARACTERS_EVENT, CDATA_EVENT, IGNORABLE_WHITESPACE_EVENT, COMMENT_EVENT, PI_EVENT,
  /// ENTITY_REFERENCE_EVENT, DEC_CHAR_REFERENCE_EVENT, and HEX_CHAR_REFERENCE_EVENT
  FAXPP_Text value;

  unsigned int attr_count; ///< The number of attributes in the event. \details Present for event types START_ELEMENT_EVENT, and SELF_CLOSING_ELEMENT_EVENT
  FAXPP_Attribute *attrs;  ///< Array of attributes. \details Present for event types START_ELEMENT_EVENT, and SELF_CLOSING_ELEMENT_EVENT

  FAXPP_Text version;      ///< The version of the event. \details Present for event types START_DOCUMENT_EVENT and START_EXTERNAL_ENTITY_EVENT
  FAXPP_Text encoding;     ///< The encoding of the event. \details Present for event types START_DOCUMENT_EVENT and START_EXTERNAL_ENTITY_EVENT
  FAXPP_Text standalone;   ///< The standalone status of the event. \details Present only for the START_DOCUMENT_EVENT event type

  FAXPP_Text system_id;    ///< The system literal of the event. \details Present for event types DOCTYPE_EVENT and ENTITY_REFERENCE_EVENT
  FAXPP_Text public_id;    ///< The public ID literal of the event. \details Present for event types DOCTYPE_EVENT and ENTITY_REFERENCE_EVENT

  unsigned int line;       ///< The line number of the start of the event
  unsigned int column;     ///< The column number of the start of the event
} FAXPP_Event;

/**
 * Returns a string describing the given event type
 * \param type The event type
 * \return a string
 *
 * \relatesalso FAXPP_Event
 */
const char *FAXPP_event_to_string(FAXPP_EventType type);

#endif
