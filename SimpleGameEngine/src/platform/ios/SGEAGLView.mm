//
//  SGEAGLView.m
//  SimpleGameEngine
//
//  Created by Nao on 2018/03/21.
//  Copyright © 2018年 Nao. All rights reserved.
//

#import "SGEAGLView.h"
#import <OpenGLES/ES2/gl.h>

// Compile shader
GLuint compileShader(GLuint shaderType, const GLchar *source) {
    // Create shader object
    GLuint shader = glCreateShader(shaderType);
    // Link shader object and source code
    glShaderSource(shader, 1, &source, NULL);
    // Compile GLSL
    glCompileShader(shader);
    
    return shader;
}

@implementation SGEAGLView
{
    GLuint _shaderProgram;
}

@synthesize context=context_;

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

+ (id) viewWithFrame:(CGRect)frame
{
    return [[self alloc] initWithFrame:frame];
}

- (instancetype)initWithFrame:(CGRect)frame {
    if ((self = [super initWithFrame:frame])) {
        [self setupOpenGL];
    }
    return self;
}

- (int) getWidth
{
    CGSize bound = [self bounds].size;
    return (int)bound.width * self.contentScaleFactor;
}

- (int) getHeight
{
    CGSize bound = [self bounds].size;
    return (int)bound.height * self.contentScaleFactor;
}

- (void) layoutSubviews {
    // Set ViewPort
    glViewport(0, 0, self.frame.size.width, self.frame.size.height);
}

- (void) setupOpenGL {
    NSLog(@"SGEAGLView::setupOpenGL");
    // Layer setup
    CAEAGLLayer *layer = (CAEAGLLayer*) self.layer;
    layer.opaque = YES;
    
    // Context object setup
    context_ = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    [EAGLContext setCurrentContext:context_];
    
    // Render buffer setup
    GLuint renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    [context_ renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
    
    // Frame buffer setup
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);
    
    // Vertex shader
    const GLchar *vertShaderSource =
    "attribute mediump vec4 pos;"
    "void main() {"
    "   gl_Position = pos;"
    "}";
    
    // Create vertex shader object
    GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertShaderSource);
    
    // Fragment shader
    const GLchar *fragShaderSource =
    "void main() {"
    "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
    "}";
    
    // Create fragment shader object
    GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragShaderSource);
    
    // Create program object
    _shaderProgram = glCreateProgram();
    
    // Link vertex shader and program object
    glAttachShader(_shaderProgram, vertShader);
    
    // Link fragment shader and program object
    glAttachShader(_shaderProgram, fragShader);
    
    // Link
    glLinkProgram(_shaderProgram);
    
    // Release shader object
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    
    // Start using shader
    glUseProgram(_shaderProgram);
    
}

- (void) update {
    // Get vertex shader pos variable
    GLint posLocation = glGetAttribLocation(_shaderProgram, "pos");
    glEnableVertexAttribArray(posLocation);
    
    // Vertex data
    const GLfloat vertex[] = {
        0.0f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };
    
    // Create vertedx data
    glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 0., vertex);
    
    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

- (void) swapBuffers
{
    [context_ presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) dealloc {
    // End using shader
    glUseProgram(0);
    
    // Release shader program
    glDeleteProgram(_shaderProgram);
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
