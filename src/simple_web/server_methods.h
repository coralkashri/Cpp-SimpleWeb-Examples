
#ifndef SERVER0311_SPEC_SERVER_H
#define SERVER0311_SPEC_SERVER_H

#include "../../core/Device.h"
#include "server_classes.hpp"
#include "../../structs/StartFileStruct.h"
#include "../vectorsMethods.h"

#include <iostream>
#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <dirent.h>
#include <boost/filesystem.hpp>

thread server_thread;
Device *_d;
float MIN_FREQ = 5e6;
float MAX_FREQ = 10e9;
float MAX_GAIN = 50;
float MAX_RATE = 50e6;

namespace SimpleWeb {
    typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

    std::string demodulation_samples(std::shared_ptr<HttpServer::Request> request); // influence_type = 2 (future: input)
    std::string samples_in_freq(std::shared_ptr<HttpServer::Request> request); // influence_type = 0
    std::string noise_samples(std::shared_ptr<HttpServer::Request> request); // influence_type = 0
    std::string get_exists_records_files_list(std::shared_ptr<HttpServer::Request> request);
    std::string get_exists_records_files_details_list(std::shared_ptr<HttpServer::Request> request);
    std::string change_record_file_name(std::shared_ptr<HttpServer::Request> request);
    std::string delete_records(std::shared_ptr<HttpServer::Request> request);
    std::ostringstream change_function(std::shared_ptr<HttpServer::Request> request, float &target_freq, float &target_rate, float &target_gain);
    std::ostringstream start_record(std::shared_ptr<HttpServer::Request> request, float &target_freq, float &target_rate, float &target_gain);
    std::ostringstream get_record(std::shared_ptr<HttpServer::Request> request, float &target_freq, float &target_rate, float &target_gain); // influence_type = input
};

namespace SimpleWeb {
    void wait_for_record(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void freq_samples_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void demodulation_samples_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void noise_samples_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void update_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void start_record_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void get_record_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void get_basic_data_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void get_exists_records_files_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void get_exists_records_files_details_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void change_record_file_name_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
    void delete_records_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request);
};

namespace SimpleWeb {
    bool valid(float freq, float rate);
};

namespace SimpleWeb {
    void change_record_file_name_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        stringstream response_content;
        try {
            response_content << change_record_file_name(request);
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    << response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
            cout << "Error!";
        }
    }

    void delete_records_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        stringstream response_content;
        try {
            response_content << delete_records(request);
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    << response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
            cout << "Error!";
        }
    }

    void freq_samples_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        stringstream response_content;
        try {
            response_content << samples_in_freq(request);
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    << response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
            cout << "Error!";
        }
    }

    void noise_samples_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        stringstream response_content;
        try {
            response_content << noise_samples(request);
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    << response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
            cout << "Error!";
        }
    }

    void update_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        std::ostringstream response_content;
        try {
            float fc, fs, gain;
            fc = device.get_freq();
            fs = device.get_rate();
            gain = device.get_gain();
            response_content << change_function(request, fc, fs, gain).str();
            device.set_freq_passive(fc);
            device.set_rate_passive(fs);
            device.set_gain_passive(gain);
            device.reset_f_samples();
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
            cout << "Error!";
        }
    }

    void start_record_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        std::ostringstream response_content;
        try {
            float fc, fs, gain;
            fc = device.get_freq();
            fs = device.get_rate();
            gain = device.get_gain();
            response_content << start_record(request, fc, fs, gain).str();
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
            cout << "Error!";
        }
    }

    void get_record_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        std::ostringstream response_content;
        try {
            float fc, fs, gain;
            fc = device.get_freq();
            fs = device.get_rate();
            gain = device.get_gain();
            response_content << get_record(request, fc, fs, gain).str();
            if (response_content.str() == "0") {
                throw "Could not open the file.";
            }
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
            cout << "Error!";
        }
    }

    void get_basic_data_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        std::ostringstream response_content;
        try {
            float fc, fs, gain;
            size_t buffer_size;
            fc = device.get_freq();
            fs = device.get_rate();
            gain = device.get_gain();
            buffer_size = device.get_buffer_size();
            response_content << "{" <<
                             "\"fcRx\": " << fc << "," <<
                             "\"fsRx\": " << fs << "," <<
                             "\"gain\": " << gain << "," <<
                             "\"buffer_size\": " << buffer_size <<
                             "}";
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
            cout << "Error!";
        }
    }

    void demodulation_samples_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        std::ostringstream response_content;
        try {
            response_content << demodulation_samples(request);
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
        }
    }

    void get_exists_records_files_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        std::ostringstream response_content;
        try {
            response_content << get_exists_records_files_list(request);
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
        }
    }

    void get_exists_records_files_details_session(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        std::ostringstream response_content;
        try {
            response_content << get_exists_records_files_details_list(request);
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
        }
    }

    std::string get_exists_records_files_list(std::shared_ptr<HttpServer::Request> request) {
        DIR *dir;
        std::ostringstream records_list;
        records_list << "{\"list\": [";
        dirent *ent;
        if ((dir = opendir(_d->get_records_dir_path().c_str())) != NULL) {
            // Print all the files and directories in the path
            while ((ent = readdir(dir)) != NULL) {
                if (ent->d_type == DT_REG) {
                    std::ifstream bin_file;
                    StartFileStruct data;
                    bin_file.open(_d->get_records_dir_path() + ent->d_name, ios::binary);
                    if (bin_file.fail()) {
                        std::cout << "Can't open file: " << ent->d_name << std::endl;
                        continue;
                    }
                    bin_file.read((char *) (&data), sizeof(StartFileStruct));
                    bin_file.close();
                    records_list << "\"" << ent->d_name
                                 << (_d->get_current_files_version() != data.file_version ? ".versionError" : "")
                                 << "\",";
                }
            }
        }
        records_list << "\"\"]}";
        return records_list.str();
    }

    std::string change_record_file_name(std::shared_ptr<HttpServer::Request> request) {
        DIR *dir;
        dirent *ent;
        boost::optional<std::string> string_child;
        std::string old_name, new_name;
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(request->content, pt);
        std::string change_status = "{\"status\":0}";
        string_child = pt.get_optional<std::string>("old_name");
        bool status = 1;
        if (string_child) {
            old_name = string_child.get(); //TODO:: consider delete spaces.
            old_name += ".bin";
        } else {
            change_status = "{\"status\":0, \"error\":\"Old name didn't recived.\"}";
            status = 0;
        }
        string_child = pt.get_optional<std::string>("new_name");
        if (string_child) {
            new_name = string_child.get(); //TODO:: consider delete spaces.
            new_name += ".bin";
        } else {
            change_status = "{\"status\":0, \"error\":\"New name didn't recived.\"}";
            status = 0;
        }

        if (status && (dir = opendir(_d->get_records_dir_path().c_str())) != NULL) {
            // Print all the files and directories in the path
            while ((ent = readdir(dir)) != NULL) {
                if (ent->d_type == DT_REG && ent->d_name == old_name) {
                    std::ifstream bin_file;
                    bin_file.open(_d->get_records_dir_path() + ent->d_name, ios::binary);
                    if (bin_file.fail()) {
                        std::cout << "Can't open file: " << ent->d_name << std::endl;
                        continue;
                    }
                    bin_file.close();
                    rename((_d->get_records_dir_path() + old_name).c_str(),
                           (_d->get_records_dir_path() + new_name).c_str());

                    change_status = "{\"status\":1}";
                    break;
                }
            }
            if (change_status != "{\"status\":1}") {
                change_status = "{\"status\":0, \"error\":\"Can't find the requested record file.\"}";
                status = 0;
            }
        }
        return change_status;
    }

    std::string delete_records(std::shared_ptr<HttpServer::Request> request) {
        DIR *dir;
        dirent *ent;
        std::vector<std::string> vector_string_child;
        vector<std::string> files_list;
        std::string success_list, fail_list;

        boost::property_tree::ptree pt;
        boost::property_tree::read_json(request->content, pt);
        std::string change_status = "{\"status\":0}";


        files_list = jparser::as_vector<std::string>(pt, "list");
        bool status = 1;
        if (files_list.size() <= 0) {
            change_status = "{\"status\":0, \"error\":\"Records list didn't recived.\"}";
            status = 0;
        }

        if (status && (dir = opendir(_d->get_records_dir_path().c_str())) != NULL) {
            change_status = "{\"status\":1,";
            while ((ent = readdir(dir)) != NULL) {
                if (ent->d_type == DT_REG && VectorsMethods::search<std::string>(files_list, ent->d_name) >= 0) {
                    std::ifstream bin_file;
                    bin_file.open(_d->get_records_dir_path() + ent->d_name, ios::binary);
                    if (bin_file.fail()) {
                        std::cout << "Can't open file: " << ent->d_name << std::endl;
                        fail_list += "\"";
                        fail_list += ent->d_name;
                        fail_list += "\",";
                        continue;
                    }
                    bin_file.close();
                    remove((_d->get_records_dir_path() + ent->d_name).c_str());
                    success_list += "\"";
                    success_list += ent->d_name;
                    success_list += "\",";
                }
            }
            change_status += "\"success_list\":[" + success_list + "\"\"]," + "\"fail_list\":[" + fail_list + "\"\"]}";
        }
        return change_status;
    }

    std::string get_exists_records_files_details_list(std::shared_ptr<HttpServer::Request> request) {
        DIR *dir;
        std::ostringstream records_list;
        records_list << "{\"list\": [";
        dirent *ent;
        if ((dir = opendir(_d->get_records_dir_path().c_str())) != NULL) {
            // Print all the files and directories in the path
            while ((ent = readdir(dir)) != NULL) {
                if (ent->d_type == DT_REG) {
                    //TODO:: Get all required details from the file.
                    /// file_name    = ent->d_name
                    //TODO:: check:: time         = std::time_t last_write_time(const path& p, system::error_code* ec=0);

                    std::ifstream bin_file;
                    StartFileStruct data;
                    bin_file.open(_d->get_records_dir_path() + ent->d_name, ios::binary);
                    if (bin_file.fail()) {
                        std::cout << "Can't open file: " << ent->d_name << std::endl;
                        continue;
                    }
                    bin_file.read((char *) (&data), sizeof(StartFileStruct));
                    double start_point = (-0.5 * data.fsRx + data.fsRx / data.buffer_size) + data.fcRx;
                    double step = data.fsRx / data.buffer_size;
                    step = round(step * 10000.0) / 10000.0;
                    double seconds = floor(data.frames_count * _d->get_buffer_size() / data.fsRx * 100) / 100;
                    time_t last_change = boost::filesystem::last_write_time(_d->get_records_dir_path() + ent->d_name);
                    struct tm *time_info;
                    char buffer[80];
                    time_info = localtime(&last_change);
                    strftime(buffer, sizeof(buffer), "%d/%m/%Y %I:%M:%S", time_info);
                    std::string str(buffer);


                    records_list << "{";
                    records_list << "\"name\":\"" << ent->d_name << "\",";
                    records_list << "\"record_date\":\"" << str << "\",";

                    records_list << "\"fsRx\":" << data.fsRx << ",";
                    records_list << "\"fcRx\":" << data.fcRx << ",";
                    records_list << "\"buffer_size\":" << data.buffer_size << ",";
                    records_list << "\"record_frames_count\":" << data.frames_count << ",";
                    records_list << "\"version\":" << data.file_version << ",";
                    records_list << "\"record_seconds\":" << seconds << ",";
                    records_list << "\"start_x\": " << start_point << ",";
                    records_list << "\"is_buffers_suitable\": " << (_d->compare_buffers(data.buffer_size) ? 1 : 0);

                    bin_file.close();
                    records_list << "},";
                }
            }
        }
        records_list << "{\"current_version\": " << _d->get_current_files_version() << "}]}";
        return records_list.str();
    }

    /// Get samples in frequency domain (in json format).
    std::string samples_in_freq(std::shared_ptr<HttpServer::Request> request) {
        if (_d->get_loop_influence_type() != 0) {
            _d->set_loop_influence_type(0);
        }
        Results res;
        do {
            _d->results_queue_manager(false, res);
        } while (res.signal_serial_number == -999);
        return _d->get_samples_in_freq_json(res).str();
    }

    /// Get noise vector (Max hold + real time) in json format.
    std::string noise_samples(std::shared_ptr<HttpServer::Request> request) {
        boost::property_tree::ptree pt;
        //boost::property_tree::read_json(request->content, pt);

        if (_d->get_loop_influence_type() != 0) {
            _d->set_loop_influence_type(0);
        }
        Results res;
        do {
            _d->results_queue_manager(false, res);
        } while (res.signal_serial_number == -999);
        return _d->get_noise_samples_in_freq_json(res).str();
    }

    /// Get demodulation samples (json format).
    std::string demodulation_samples(std::shared_ptr<HttpServer::Request> request) {
        boost::property_tree::ptree pt;
        //boost::property_tree::read_json(request->content, pt);
        if (_d->get_loop_influence_type() != 2) {
            _d->set_loop_influence_type(2); // FM
        }
        Results res;
        _d->results_queue_manager(false, res);
        while (res.signal_serial_number == -999 || !res.demodulated_vector.data() ||
               res.demodulated_vector[2] + res.demodulated_vector[3] + res.demodulated_vector[4] +
               res.demodulated_vector[5] == 0) {
            _d->results_queue_manager(false, res);
        }
        return _d->get_demodulation_samples_json(res).str();
    }

    /// Change current SDR Settings.
    std::ostringstream change_function(std::shared_ptr<HttpServer::Request> request, float &target_freq, float &target_rate, float &target_gain) {

        std::ostringstream result;
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(request->content, pt);
        boost::optional<float> child;
        float temp_freq = target_freq;
        float temp_rate = target_rate;
        float temp_gain = target_gain;
        bool is_requested_value = false;
        bool is_valid = false;

        child = pt.get_optional<float>("freq");
        if (child) {
            temp_freq = child.get();
            is_requested_value = true;
            is_valid = true;
        } else {
            is_valid = false;
        }

        child = pt.get_optional<float>("rate");
        if (child) {
            temp_rate = child.get();
            if (_d->get_loop_influence_type() < 2) {
                is_requested_value = true;
                is_valid = is_valid && true;
            } else {
                temp_rate = min(float(300e3), temp_rate);
            }
        } else {
            is_valid = false;
        }

        child = pt.get_optional<float>("gain");
        if (child) {
            temp_gain = child.get();
            is_requested_value = true;
            is_valid = is_valid && true;
        } else {
            is_valid = false;
        }

        if (!is_requested_value) {
            throw "Request content is not suitable";
        }

        if (valid(temp_freq, temp_rate) && is_valid) {
            target_freq = temp_freq;
            target_rate = temp_rate;
            _d->reset_f_samples();
            is_valid = true;
        }

        if (temp_gain <= MAX_GAIN) {
            target_gain = temp_gain;
            _d->reset_f_samples();
            is_valid = is_valid && true;
        }

        result << "{\"freq\": " << target_freq << ", \"rate\": " << target_rate << ", \"gain\": " << target_gain
               << ", \"is_updated\": " << (is_valid ? "true" : "false") << "}";
        return result;
    }

    /// The function creates a new record according to the current sdr variables.
    std::ostringstream start_record(std::shared_ptr<HttpServer::Request> request, float &target_freq, float &target_rate, float &target_gain) {
        std::ostringstream result;
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(request->content, pt);  // TODO ask -throws exception without massage ??
        boost::optional<int> int_child;
        boost::optional<string> string_child;
        string file_name = "";
        int pictures_count = 0;
        bool is_valid;

        string_child = pt.get_optional<string>("file_name");
        if (string_child) {
            file_name = string_child.get(); //TODO:: consider delete spaces.
        }

        int_child = pt.get_optional<int>("pictures_count");
        if (int_child) {
            pictures_count = int_child.get();
        }

        is_valid = file_name != "" && pictures_count > 0;

        if (is_valid) {
            file_name += ".bin";
            _d->set_file_name(file_name);
            _d->update_file_str();
            _d->set_file_pictures_count((size_t) pictures_count);
            _d->set_up_recording_flag();
        }

        result << "{\"record_validation\": " << is_valid << " , \"freq\": " << target_freq << ", \"rate\": "
               << target_rate << ", \"gain\": " << target_gain << "}";
        return result;
    }

    /// The function returns a record's json in the frequency domain.
    std::ostringstream get_record(std::shared_ptr<HttpServer::Request> request, float &target_freq, float &target_rate, float &target_gain) {

        std::ostringstream result;
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(request->content, pt);  // TODO ask -throws exception without massage ??
        boost::optional<int> int_child;
        boost::optional<string> string_child;
        string file_name = "";
        int time_average_count;
        int influence_type;
        bool is_valid;

        string_child = pt.get_optional<string>("file_name");
        if (string_child) {
            file_name = string_child.get();
        }

        int_child = pt.get_optional<int>("time_average");
        if (int_child) {
            time_average_count = int_child.get();
            if (time_average_count < 1) {
                time_average_count = 1;
            }
        } else {
            time_average_count = 1;
        }

        int_child = pt.get_optional<int>("influence_type");
        if (int_child) {
            influence_type = int_child.get();
            if (influence_type < 0) {
                influence_type = 0;
            }
        } else {
            influence_type = 0;
        }

        is_valid = file_name != "";

        if (is_valid) {
            file_name += ".bin";
            _d->set_file_name(file_name);
            _d->update_file_str();
            _d->update_time_average_in_sending_record(time_average_count);
            if (_d->get_loop_influence_type() != (size_t) influence_type) {
                _d->set_loop_influence_type((size_t) influence_type);
            }
            result << _d->get_record_json().str();
        } else {
            result << "{\"record_validation\": false, \"freq\": " << target_freq << ", \"rate\": "
                   << target_rate << ", \"gain\": " << target_gain << "}";
        }
        return result;
    }

    void wait_for_record(Device &device, SimpleWeb::ServerBase<SimpleWeb::HTTP>::Response &response, const shared_ptr<SimpleWeb::ServerBase<SimpleWeb::HTTP>::Request> &request) {
        stringstream response_content;
        try {
            while (!device.is_recording()); // Wait until the server will update the recording flag to 'true'.
            while (device.is_recording()); // Wait until the server will finish the recording.

            response_content << "{\"recording_status\": \"finished\"}";
            response
                    << "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    << response_content.str().length() << "\r\n\r\n" << response_content.str();
        }
        catch (char const *e) {
            response
                    << "HTTP/1.1 400 Error\r\nContent-Type: text/plain; charset=UTF-8\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: "
                    <<
                    strlen(e) << "\r\n\r\n" << e;
            cout << "Error!";
        }
    }

    bool valid(float freq, float rate) {
        float start_freq = freq - rate / 2;
        float end_freq = freq + rate / 2;

        return MIN_FREQ <= start_freq && end_freq <= MAX_FREQ && rate <= MAX_RATE;
    }
};

namespace SimpleWeb {
    void init(HttpServer &server, Device &device);
    void init_routes(HttpServer &server, Device &device);
    void start(HttpServer &server);
    void stop(HttpServer &server);

    /// Run the server
    void start(HttpServer &server) {
        server_thread = std::thread([&server]() { server.start(); });
        std::cout << "Server is running" << std::endl;
    }

    /// Stop the server.
    void stop(HttpServer &server) {
        server.stop();
        std::cout << "Server is stopped" << std::endl;
        server_thread.join();
        std::cout << "Server thread is stopped" << std::endl;
    }

    void init(HttpServer &server, Device &device) {
        _d = &device;
        init_routes(server, device);
        start(server);
    }

    void init_routes(HttpServer &server, Device &device) {
        server.resource["^/DemodulationSamples$"]["POST"] = [&device](HttpServer::Response &response,
                                                                      std::shared_ptr<HttpServer::Request> request) {
            demodulation_samples_session(device, response, request);
        };
        server.resource["^/DemodulationSamples$"]["GET"] = [&device](HttpServer::Response &response,
                                                                     std::shared_ptr<HttpServer::Request> request) {
            demodulation_samples_session(device, response, request);
        };
        server.resource["^/FreqSamples$"]["POST"] = [&device](HttpServer::Response &response,
                                                              std::shared_ptr<HttpServer::Request> request) {
            freq_samples_session(device, response, request);
        };
        server.resource["^/NoiseSamples$"]["POST"] = [&device](HttpServer::Response &response,
                                                               std::shared_ptr<HttpServer::Request> request) {
            noise_samples_session(device, response, request);
        };
        server.resource["^/FreqSamples$"]["GET"] = [&device](HttpServer::Response &response,
                                                             std::shared_ptr<HttpServer::Request> request) {
            freq_samples_session(device, response, request);
        };
        server.resource["^/Update$"]["POST"] = [&device](HttpServer::Response &response,
                                                         std::shared_ptr<HttpServer::Request> request) {
            update_session(device, response, request);
        };
        server.resource["^/StartRecord$"]["POST"] = [&device](HttpServer::Response &response,
                                                              std::shared_ptr<HttpServer::Request> request) {
            start_record_session(device, response, request);
        };
        server.resource["^/GetRecord$"]["POST"] = [&device](HttpServer::Response &response,
                                                            std::shared_ptr<HttpServer::Request> request) {
            get_record_session(device, response, request);
        };
        server.resource["^/GetBasicData$"]["POST"] = [&device](HttpServer::Response &response,
                                                               std::shared_ptr<HttpServer::Request> request) {
            get_basic_data_session(device, response, request);
        };
        server.resource["^/WaitForRecord$"]["POST"] = [&device](HttpServer::Response &response,
                                                                std::shared_ptr<HttpServer::Request> request) {
            wait_for_record(device, response, request);
        };
        server.resource["^/GetRecFilesList$"]["POST"] = [&device](HttpServer::Response &response,
                                                                  std::shared_ptr<HttpServer::Request> request) {
            get_exists_records_files_session(device, response, request);
        };
        server.resource["^/GetFilesDetails$"]["POST"] = [&device](HttpServer::Response &response,
                                                                  std::shared_ptr<HttpServer::Request> request) {
            get_exists_records_files_details_session(device, response, request);
        };
        server.resource["^/ChangeRecordName$"]["POST"] = [&device](HttpServer::Response &response,
                                                                   std::shared_ptr<HttpServer::Request> request) {
            change_record_file_name_session(device, response, request);
        };
        server.resource["^/DeleteRecordFiles$"]["POST"] = [&device](HttpServer::Response &response,
                                                                    std::shared_ptr<HttpServer::Request> request) {
            delete_records_session(device, response, request);
        };
    }

};
#endif //SERVER0311_SPEC_SERVER_H