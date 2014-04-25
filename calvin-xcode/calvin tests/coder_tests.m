//
//  coder_tests.m
//  Calvin
//
//  Created by Per Persson on 2014-04-24.
//
//

#import <XCTest/XCTest.h>
#import "actors-coder.h"

#define TX_DATA decoder->set_data(decoder, coder->data(coder))

#define ARRAY_LEN 3
#define MAX_STRING_SIZE 256
typedef struct {int a; int b;} struct_t;

@interface coder_tests : XCTestCase
{
  ActorCoder *coder;
  ActorCoder *decoder;
}
@end

@implementation coder_tests

- (void)setUp
{
  [super setUp];
  coder = newCoder(JSON_CODER);
  decoder = newCoder(JSON_CODER);
}

- (void)tearDown
{
  destroyCoder(coder);
  destroyCoder(decoder);
  [super tearDown];
}

- (void)testIntTypeEncodeDecode
{
  int original = 732654;
  int target = 0;
  const char *type = "i";

  XCTAssertNotEqual(target, original, "Bad setup");
  
  CoderState *state = coder->init(coder);

  coder->encode(coder, state, "key", &original, type);
  coder->decode(coder, state, "key", &target, type);

  XCTAssertEqual(target, original, "Coding of type \"%s\"failed", type);
}

- (void)testIntTypeEncodeTxDecode
{
  int original = 732654;
  int target = 0;
  const char *type = "i";
  
  XCTAssertNotEqual(target, original, "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  coder->encode(coder, state, "key", &original, type);
  TX_DATA;
  decoder->decode(coder, state, "key", &target, type);
  
  XCTAssertEqual(target, original, "Coding of type \"%s\"failed", type);
}


- (void)testStringTypeEncodeDecode
{
  const char *original = "hello";
  char *target = NULL;
  const char *type = "s";
  
  XCTAssertEqual(target, NULL, "Bad setup");
  XCTAssertNotEqual(original, NULL, "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  coder->encode(coder, state, "key", &original, type);
  coder->decode(coder, state, "key", &target, type);

  XCTAssertEqual(strncmp(target, original, strlen(original)), 0, "Coding of type \"%s\" failed", type);
  free(target);
}

- (void)testFloatTypeEncodeDecode
{
  float original = 732.654;
  float target = 0;
  const char *type = "f";
  
  XCTAssertNotEqual(target, original, "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  coder->encode(coder, state, "key", &original, type);
  coder->decode(coder, state, "key", &target, type);
  
  XCTAssertEqual(target, original, "Coding of type \"%s\" failed", type);
}

- (void)testArrayEncodeDecode
{
  int original[ARRAY_LEN] = {1,2,3};
  int target[ARRAY_LEN] = {0};
  
  XCTAssertNotEqual(target[0], original[0], "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  CoderState *array = coder->encode_array(coder, state, "key");
  for (int i = 0; i<ARRAY_LEN; i++) {
    coder->encode(coder, array, NULL, &original[i], "i");
  }
  
  array = coder->decode_array(coder, state, "key");
  for (int i = 0; i<ARRAY_LEN; i++) {
    coder->decode(coder, array, NULL, &target[i], "i");
    XCTAssertEqual(target[i], original[i], "Coding of array failed");
  }
}

- (void)testStructEncodeDecode
{
  struct_t original = {1,2};
  struct_t target = {0};
  
  XCTAssertNotEqual(target.a, original.a, "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  CoderState *strct = coder->encode_struct(coder, state, "key");
  coder->encode(coder, strct, "a", &original.a, "i");
  coder->encode(coder, strct, "b", &original.b, "i");
  
  strct = coder->decode_struct(coder, state, "key");
  coder->decode(coder, strct, "a", &target.a, "i");
  coder->decode(coder, strct, "b", &target.b, "i");
  
  XCTAssertEqual(target.a, original.a, "Coding of struct failed");
  XCTAssertEqual(target.b, original.b, "Coding of struct failed");
}

- (void)testArrayOfStructsEncodeDecode
{
  struct_t original[ARRAY_LEN] = {{1,2},{3,4},{5,6}};
  struct_t target[ARRAY_LEN] = {0};
  
  XCTAssertNotEqual(target[0].a, original[0].a, "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  CoderState *array = coder->encode_array(coder, state, "key");
  for (int i = 0; i<ARRAY_LEN; i++) {
    CoderState *strct = coder->encode_struct(coder, array, "dummy");
    coder->encode(coder, strct, "a", &original[i].a, "i");
    coder->encode(coder, strct, "b", &original[i].b, "i");
  }
  
  array = coder->decode_array(coder, state, "key");
  XCTAssert(array != NULL, "decode_array returned bad state");
  for (int i = 0; i<ARRAY_LEN; i++) {
    CoderState *strct = coder->decode_struct(coder, array, "dummy");
    coder->decode(coder, strct, "a", &target[i].a, "i");
    coder->decode(coder, strct, "b", &target[i].b, "i");
    XCTAssertEqual(target[i].a, original[i].a, "Coding of array of structs failed");
    XCTAssertEqual(target[i].b, original[i].b, "Coding of array of structs failed");
  }
}

- (void)testStructOfArraysEncodeDecode
{
  struct {int a[ARRAY_LEN]; int b[ARRAY_LEN];} original = {.a={1,2,3}, .b={4,5,6}};
  struct {int a[ARRAY_LEN]; int b[ARRAY_LEN];} target = {0};
  
  XCTAssertNotEqual(target.a[0], original.a[0], "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  CoderState *strct = coder->encode_struct(coder, state, "key");
  CoderState *array_a = coder->encode_array(coder, strct, "a");
  CoderState *array_b = coder->encode_array(coder, strct, "b");
  for (int i = 0; i<ARRAY_LEN; i++) {
    coder->encode(coder, array_a, NULL, &original.a[i], "i");
    coder->encode(coder, array_b, NULL, &original.b[i], "i");
  }
  
  strct = coder->decode_struct(coder, state, "key");
  XCTAssert(strct != NULL, "decode_struct returned bad state");
  array_a = coder->decode_array(coder, strct, "a");
  array_b = coder->decode_array(coder, strct, "b");
  for (int i = 0; i<ARRAY_LEN; i++) {
    coder->decode(coder, array_a, NULL, &target.a[i], "i");
    coder->decode(coder, array_b, NULL, &target.b[i], "i");
    XCTAssertEqual(target.a[i], original.a[i], "Coding of struct of arrays failed");
    XCTAssertEqual(target.b[i], original.b[i], "Coding of struct of arrays failed");
  }
}

- (void)testJSONDataFormat
{
    int original = 732654;
    int target = 0;
    const char *type = "i";
    const char *key = "key";
    char expected[MAX_STRING_SIZE];
    
    snprintf(expected, MAX_STRING_SIZE, "{\"%s\":%d}", key, original);
    
    CoderState *state = coder->init(coder);
    coder->encode(coder, state, key, &original, type);
    const char *json = coder->data(coder);
    XCTAssert(strncmp(json, expected, MAX_STRING_SIZE) == 0, "Wrong JSON format");
    
    state = decoder->set_data(decoder, (void *)json);
    decoder->decode(decoder, state, key, &target, type);
    
    XCTAssertEqual(target, original, "Coding of type \"%s\"failed", type);
}


@end
