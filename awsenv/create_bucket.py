import boto3
from botocore.exceptions import ClientError

BUCKET_NAME = 'bob10-4249-test'
AWS_ACCESS_KEY = 'AKIAWHPSCFE25U35HYPB'
AWS_SECRET_ACCESS_KEY = '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'

##test_bucket_create
def create_s3_bucket(bucket_name):
    s3 = boto3.client(
        's3',
        aws_access_key_id=AWS_ACCESS_KEY,
        aws_secret_access_key=AWS_SECRET_ACCESS_KEY
    )
    try:
        response = s3.create_bucket(
            Bucket=bucket_name,
            CreateBucketConfiguration={
                'LocationConstraint': 'ap-northeast-2'
            }
        )
        return response
    except ClientError as e:
        print("Error")