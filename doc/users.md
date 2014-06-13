# API Reference (1.0)
---

## 1. users（ajax）

### url
http://x.x.x.x/api/1.0/users.json

### 支持格式
JSON

### HTTP请求方式
GET  
PUT
POST
DELETE

### 是否需要登录
是

### 请求参数
 请求|参数|必选|类型及范围|说明
---|---|:-:|---|---|---
GET|items|是|array: ['password', 'privilege']|是否需要返回用户密码和特权级
PUT|items|是|object: [ {'username':'username', 'password':'password', 'privilege':0}]|所有需要设置的用户名，密码，特权级的数组，允许一次调用设置多个用户
POST|items|是|object: [ {'username':'username', 'password':'password', 'privilege':0}]|目前POST和PUT功能完全一样，都是可以增加用户，修改用户信息
DELETE|items|是|object: [ { 'username':'user1' }, { 'username':'user2' } ]|需要被删除的用户名，可以一次删除多个

### 注意事项
无

### 调用样例
GET http://x.x.x.x/api/1.0/users.json&items%5B%5D=password&items%5B%5D=privilege
PUT http://x.x.x.x/api/1.0/users.json json_data

### 返回结果
JSON示例
GET

	{
		'items': [
			{
				'username':'admin',
				'password':'passwd',
				'privilege':1
			},
			{
				'username':'guest',
				'password':'passwd',
				'privilege':0
			}
		]
	}
	
PUT

	{'success': 'true' | 'false'}
	
### 返回字段说明
返回值字段|字段类型|字段说明
---|---|---
username|string|用户名
password|string|密码
privilege|int|是否特权用户

## 2. users（message）

### 2.1 get_users
#### request
    {
		'head': {
        	'action': 'get_users',
            'version': '1.0'
		},
        'body': {
            'items': [
                'password',
                'privilege'
            ]
        }
    }
#### response
    {
		'head': {
            'action': 'get_users',
            'version': '1.0',
		    'code': '0'
		},
        'body': {
		    'items': [
                {
                    'username':'admin',
                    'password':'passwd',
                    'privilege':1
                }
                {
                    'username':'guest',
                    'password':'passwd',
                    'privilege':0
                }
            ]
        }
    }
---
### 2.2 set_users
#### request
    {
		'head': {
		    'action': 'set_users',
            'version': '1.0'
        },
        'body': {
			'items': [
                {
                    'username':'user1',
                    'password':'passwd',
                    'privilege':0
                },
                {
                    'username':'user2',
                    'password':'passwd',
                    'privilege':0
                }
			]
		}
    }
#### response
    {
		'head': {
    		'action': 'set_users',
            'version': '1.0',
			'code': '0'
		},
        'body': {
		}
    }
### 2.3 add_users
#### request
    {
		'head': {
		    'action': 'set_users',
            'version': '1.0'
        },
        'body': {
			'items': [
                {
                    'username':'user1',
                    'password':'passwd',
                    'privilege':0
                },
                {
                    'username':'user2',
                    'password':'passwd',
                    'privilege':0
                }
			]
		}
    }
#### response
    {
		'head': {
    		'action': 'set_users',
            'version': '1.0',
			'code': '0'
		},
        'body': {
		}
    }
### 2.4 del_users
#### request
    {
		'head': {
		    'action': 'set_users',
            'version': '1.0'
        },
        'body': {
			'items': [
                {
                    'username':'user1',
                },
                {
                    'username':'user2',
                }
			]
		}
    }
#### response
    {
		'head': {
    		'action': 'set_users',
            'version': '1.0',
			'code': '0'
		},
        'body': {
		}
    }