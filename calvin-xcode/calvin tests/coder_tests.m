//
//  coder_tests.m
//  Calvin
//
//  Created by Per Persson on 2014-04-24.
//
//

#import <XCTest/XCTest.h>
#import "actors-coder.h"


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


@end
