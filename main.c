﻿#include <json/json.h>
#include <stdio.h>
 
void print_json_value(json_object *jobj){
    
    enum json_type type;
    
    printf("type: ",type);
    type = json_object_get_type(jobj);

    switch (type) {
        case json_type_boolean:
            printf("json_type_boolean\n");
            printf("value: %s\n",
                    json_object_get_boolean(jobj)? "true": "false");
            break;
      case json_type_double:
            printf("json_type_double\n");
            printf("          value: %lf\n",
                    json_object_get_double(jobj));
            break;
      case json_type_int:
            printf("json_type_int\n");
            printf("          value: %d\n",
                    json_object_get_int(jobj));
            break;
      case json_type_string:
            printf("json_type_string\n");
            printf("          value: %s\n",
                    json_object_get_string(jobj));
            break;
    }
 
}
 

void json_parse_array( json_object *jobj, char *key) {
    void json_parse(json_object * jobj);
    enum json_type type;
    
    json_object *jarray = jobj;
    if(key) {
        jarray = json_object_object_get(jobj, key);
    }
 
    int arraylen = json_object_array_length(jarray);
    printf("Array Length: %d\n",arraylen);
    int i;
    json_object * jvalue;

    for (i=0; i< arraylen; i++){

        jvalue = json_object_array_get_idx(jarray, i);
        type = json_object_get_type(jvalue);
        if (type == json_type_array) {
            json_parse_array(jvalue, NULL);
        }
        else if (type != json_type_object) {
            printf("value[%d]: ",i);
            print_json_value(jvalue);
        }
        else {
            json_parse(jvalue);
        }

    }

}
 

void json_parse(json_object * jobj) {
    
    enum json_type type;
    json_object_object_foreach(jobj, key, val) {
        
        printf("type: ",type);
        type = json_object_get_type(val);
        switch (type) {
            case json_type_boolean:
            case json_type_double:
            case json_type_int:
            case json_type_string:
                print_json_value(val);
                break;
            case json_type_object:
                printf("json_type_object\n");
                jobj = json_object_object_get(jobj, key);
                json_parse(jobj);
                break;
            case json_type_array:
                printf("type: json_type_array, ");
                json_parse_array(jobj, key);
                break;
        }

    }

} 


int main() {
    char * string = "{\"name\" : \"nql\",\
                     \"cat\" : [ \"c\" , [\"c++\" , \"c\" ], \"python\" ],\
                     \"all\": { \"admin\": false, \"name\" : \"nql\", \"Number of Posts\" : 10 } \
                     }";
    printf("JSON string: %s\n", string);
    json_object * jobj = json_tokener_parse(string);
    json_parse(jobj);
}
