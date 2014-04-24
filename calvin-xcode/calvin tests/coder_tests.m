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

  coder->encode(state, "key", &original, type);
  coder->decode(state, "key", &target, type);

  XCTAssertEqual(target, original, "Coding of type \"%s\"failed", type);
}

- (void)testIntTypeEncodeTxDecode
{
  int original = 732654;
  int target = 0;
  const char *type = "i";
  
  XCTAssertNotEqual(target, original, "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  coder->encode(state, "key", &original, type);
  TX_DATA;
  decoder->decode(state, "key", &target, type);
  
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
  
  coder->encode(state, "key", &original, type);
  coder->decode(state, "key", &target, type);

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
  
  coder->encode(state, "key", &original, type);
  coder->decode(state, "key", &target, type);
  
  XCTAssertEqual(target, original, "Coding of type \"%s\" failed", type);
}

- (void)testArrayEncodeDecode
{
  int original[ARRAY_LEN] = {1,2,3};
  int target[ARRAY_LEN] = {0};
  const char *type = "i";
  
  XCTAssertNotEqual(target[0], original[0], "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  CoderState *array = coder->encode_array(state, "key");
  for (int i = 0; i<ARRAY_LEN; i++) {
    coder->encode(array, NULL, &original[i], "i");
  }
  
  array = coder->decode_array(state, "key");
  for (int i = 0; i<ARRAY_LEN; i++) {
    coder->decode(array, NULL, &target[i], "i");
    XCTAssertEqual(target[i], original[i], "Coding of type \"%s\" failed", type);
  }
}

- (void)testStructEncodeDecode
{
  struct_t original = {1,2};
  struct_t target = {0};
  const char *type = "i";
  
  XCTAssertNotEqual(target.a, original.a, "Bad setup");
  
  CoderState *state = coder->init(coder);
  
  CoderState *strct = coder->encode_struct(state, "key");
  coder->encode(strct, "a", &original.a, "i");
  coder->encode(strct, "b", &original.b, "i");
  
  strct = coder->decode_struct(state, "key");
  coder->decode(strct, "a", &target.a, "i");
  coder->decode(strct, "b", &target.b, "i");
  
  XCTAssertEqual(target.a, original.a, "Coding of type \"%s\" failed", type);
  XCTAssertEqual(target.b, original.b, "Coding of type \"%s\" failed", type);
}

@end
