//
//  MJPropertyKey.h
//  MJExtensionExample
//
//  Created by MJ Lee on 15/8/11.
//  Copyright (c) 2015年 小码哥. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    QNMJPropertyKeyTypeDictionary = 0, // 字典的key
    QNMJPropertyKeyTypeArray // 数组的key
} QNMJPropertyKeyType;

/**
 *  属性的key
 */
@interface QNPropertyKey : NSObject
/** key的名字 */
@property (copy,   nonatomic) NSString *name;
/** key的种类，可能是@"10"，可能是@"age" */
@property (assign, nonatomic) QNMJPropertyKeyType type;

/**
 *  根据当前的key，也就是name，从object（字典或者数组）中取值
 */
- (id)valueInObject:(id)object;

@end
