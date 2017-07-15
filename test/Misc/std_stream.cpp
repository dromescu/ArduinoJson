// Copyright Benoit Blanchon 2014-2017
// MIT License
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!

#include <ArduinoJson.h>
#include <catch.hpp>
#include <sstream>

TEST_CASE("std::stream") {
  SECTION("JsonVariantFalse") {
    std::ostringstream os;
    DynamicJsonVariant variant;
    variant = false;
    os << variant;
    REQUIRE("false" == os.str());
  }

  SECTION("JsonVariantString") {
    std::ostringstream os;
    DynamicJsonVariant variant("coucou");
    os << variant;
    REQUIRE("\"coucou\"" == os.str());
  }

  SECTION("JsonObject") {
    std::ostringstream os;
    DynamicJsonObject object;
    object["key"] = "value";
    os << object;
    REQUIRE("{\"key\":\"value\"}" == os.str());
  }

  SECTION("JsonObjectSubscript") {
    std::ostringstream os;
    DynamicJsonObject object;
    object["key"] = "value";
    os << object["key"];
    REQUIRE("\"value\"" == os.str());
  }

  SECTION("JsonArray") {
    std::ostringstream os;
    DynamicJsonArray array;
    array.add("value");
    os << array;
    REQUIRE("[\"value\"]" == os.str());
  }

  SECTION("JsonArraySubscript") {
    std::ostringstream os;
    DynamicJsonArray array;
    array.add("value");
    os << array[0];
    REQUIRE("\"value\"" == os.str());
  }

  SECTION("ParseArray") {
    std::istringstream json(" [ 42 /* comment */ ] ");
    DynamicJsonArray arr;
    bool result = parseJson(arr, json);
    REQUIRE(result == true);
    REQUIRE(true == arr.success());
    REQUIRE(1 == arr.size());
    REQUIRE(42 == arr[0]);
  }

  SECTION("ParseObject") {
    std::istringstream json(" { hello : world // comment\n }");
    DynamicJsonObject obj;
    bool result = parseJson(obj, json);
    REQUIRE(result == true);
    REQUIRE(1 == obj.size());
    REQUIRE(std::string("world") == obj["hello"]);
  }

  SECTION("ShouldNotReadPastTheEnd") {
    std::istringstream json("{}123");
    DynamicJsonObject obj;
    parseJson(obj, json);
    REQUIRE('1' == json.get());
  }
}
