//
//  VideoViewRender.m
//  baseVideo
//
//  Created by 3tee on 2019/5/27.
//  Copyright © 2019 Elliot. All rights reserved.
//

#import "VideoViewRender.h"

@implementation VideoViewRender

- (instancetype)init{
    if (self = [super init]) {
        self.layer.borderWidth = .5f;
        self.layer.borderColor = [UIColor whiteColor].CGColor;
    }
    return self;
}

@end
