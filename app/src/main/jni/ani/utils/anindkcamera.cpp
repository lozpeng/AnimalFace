//
// Created by lozpeng on 2024/1/30.
//

#include "anindkcamera.hpp"
#include "AniAI.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/calib3d/calib3d.hpp>

#include "AniAI.hpp"

namespace ani {
    static int draw_unsupported(cv::Mat& rgb)
    {
        const char text[] = "YoloModel UnInited";

        int baseLine = 0;
        cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.0, 1, &baseLine);

        int y = (rgb.rows - label_size.height) / 2;
        int x = (rgb.cols - label_size.width) / 2;

        cv::rectangle(rgb, cv::Rect(cv::Point(x, y), cv::Size(label_size.width, label_size.height + baseLine)),
                      cv::Scalar(255, 255, 255), -1);

        cv::putText(rgb, text, cv::Point(x, y + label_size.height),
                    cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 0));

        return 0;
    }

    static int draw_fps(cv::Mat& rgb)
    {
        // resolve moving average
        float avg_fps = 0.f;
        {
            static double t0 = 0.f;
            static float fps_history[10] = {0.f};

            double t1 = ncnn::get_current_time();
            if (t0 == 0.f)
            {
                t0 = t1;
                return 0;
            }

            float fps = 1000.f / (t1 - t0);
            t0 = t1;

            for (int i = 9; i >= 1; i--)
            {
                fps_history[i] = fps_history[i - 1];
            }
            fps_history[0] = fps;

            if (fps_history[9] == 0.f)
            {
                return 0;
            }

            for (int i = 0; i < 10; i++)
            {
                avg_fps += fps_history[i];
            }
            avg_fps /= 10.f;
        }

        char text[32];
        sprintf(text, "FPS=%.2f", avg_fps);

        int baseLine = 0;
        cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

        int y = 0;
        int x = rgb.cols - label_size.width;

        cv::rectangle(rgb, cv::Rect(cv::Point(x, y), cv::Size(label_size.width, label_size.height + baseLine)),
                      cv::Scalar(255, 255, 255), -1);

        cv::putText(rgb, text, cv::Point(x, y + label_size.height),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));

        return 0;
    }

    void AniNdkCamera::on_image_render(cv::Mat& rgb) const
    {
        // nanodet
        {
            ncnn::MutexLockGuard g(lock);
            if (g_yolo)
            {
                std::vector<Object> objects;
                g_yolo->detect(rgb, objects);

                g_yolo->draw(rgb, objects);
                __android_log_print(ANDROID_LOG_DEBUG, "AniNdkCamera", "ImageRendered");
            }
            else
            {
                draw_unsupported(rgb);
            }
        }

        draw_fps(rgb);
    }

} // ani