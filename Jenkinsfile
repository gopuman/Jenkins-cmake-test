pipeline {
    agent any

    stages {
        stage('Checkout Code') {
            steps {
                // Checkout code from Git
                git 'https://your-repo-url.git'
            }
        }
        stage('Configure and Build') {
            steps {
                // Run CMake and make
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
                // Run ctest
                sh '''
                cd build
                ctest --verbose
                '''
            }
        }
        stage('Archive Artifacts') {
            steps {
                // Archive build artifacts
                archiveArtifacts artifacts: 'build/**', fingerprint: true

                // Publish test results (if XML is available)
                junit 'build/Testing/**/*.xml'
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
