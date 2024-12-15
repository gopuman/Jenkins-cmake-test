pipeline {
    agent any

    environment {
        PATH = "/usr/bin:$PATH" // Replace "/usr/bin" with the directory where cmake is installed
    }

    stages {
        stage('Checkout Code') {
            steps {
                git 'https://github.com/gopuman/Jenkins-cmake-test'
            }
        }
        stage('Configure and Build') {
            steps {
                sh '''
                mkdir -p build
                cd build
                cmake ..
                make
                '''
            }
        }
        stage('Run Tests') {
            steps {
                sh '''
                cd build
                ctest --verbose
                '''
            }
        }
        stage('Archive Artifacts') {
            steps {
                archiveArtifacts artifacts: 'build/**', fingerprint: true
            }
        }
    }

    post {
        always {
            echo 'Pipeline completed.'
        }
        failure {
            echo 'Build failed.'
        }
    }
}
