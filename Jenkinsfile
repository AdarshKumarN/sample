pipeline {
    agent any

    environment {
        BUILD_DIR = "build"
    }

    stages {

        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Configure') {
            steps {
                sh '''
                set -e
                cmake -S . -B ${BUILD_DIR} \
                      -DENABLE_TESTS=ON \
                      -DENABLE_COVERAGE=OFF
                '''
            }
        }

        stage('Build') {
            steps {
                sh '''
                set -e
                cmake --build ${BUILD_DIR}
                '''
            }
        }

        stage('Test') {
            steps {
                sh '''
                set -e
                ctest --test-dir ${BUILD_DIR} --output-on-failure
                '''
            }
        }
    }

    post {
        success {
            echo 'Build and tests completed successfully'
        }
        failure {
            echo 'Pipeline failed – check logs'
        }
        always {
            archiveArtifacts artifacts: 'build/**', allowEmptyArchive: true
        }
    }
}
